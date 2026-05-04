/*
 *  SEController.m
 *  SkyEmu iOS Controller
 *
 *  Objective-C wrapper for emulator input
 */

#import "SEController.h"
#include "../shared.h"
#include "../main.h"

// External declarations
extern sb_emu_state_t emu_state;
extern sb_gui_state_t gui_state;

// Button layout constants
static const CGFloat SE_BUTTON_SIZE = 60.0;
static const CGFloat SE_BUTTON_SPACING = 10.0;
static se_system_t g_system = SE_SYSTEM_GB;

// Button positions for GBA-style layout
typedef struct {
    se_button_t button;
    NSString *name;
    CGFloat x, y;
} SEButtonLayout;

static SEButtonLayout SEGBAButtons[] = {
    {SE_BUTTON_A, @"A", 1.0 - (SE_BUTTON_SIZE + SE_BUTTON_SPACING) / 320.0, 1.0 - (SE_BUTTON_SIZE + SE_BUTTON_SPACING) / 480.0},
    {SE_BUTTON_B, @"B", 1.0 - (SE_BUTTON_SIZE * 2 + SE_BUTTON_SPACING * 2) / 320.0, 1.0 - (SE_BUTTON_SIZE + SE_BUTTON_SPACING) / 480.0},
    {SE_BUTTON_X, @"X", 1.0 - (SE_BUTTON_SIZE + SE_BUTTON_SPACING) / 320.0, 1.0 - (SE_BUTTON_SIZE * 2 + SE_BUTTON_SPACING * 2) / 480.0},
    {SE_BUTTON_Y, @"Y", 1.0 - (SE_BUTTON_SIZE * 2 + SE_BUTTON_SPACING * 2) / 320.0, 1.0 - (SE_BUTTON_SIZE * 2 + SE_BUTTON_SPACING * 2) / 480.0},
    {SE_BUTTON_UP, @"↑", 160.0 / 320.0, 1.0 - (SE_BUTTON_SIZE * 3 + SE_BUTTON_SPACING * 3) / 480.0},
    {SE_BUTTON_DOWN, @"↓", 160.0 / 320.0, 1.0 - (SE_BUTTON_SIZE * 4 + SE_BUTTON_SPACING * 4) / 480.0},
    {SE_BUTTON_LEFT, @"←", 160.0 / 320.0 - (SE_BUTTON_SIZE + SE_BUTTON_SPACING) / 320.0, 1.0 - (SE_BUTTON_SIZE * 3 + SE_BUTTON_SPACING * 3) / 480.0},
    {SE_BUTTON_RIGHT, @"→", 160.0 / 320.0 + (SE_BUTTON_SIZE + SE_BUTTON_SPACING) / 320.0, 1.0 - (SE_BUTTON_SIZE * 3 + SE_BUTTON_SPACING * 3) / 480.0},
    {SE_BUTTON_L, @"L", 0.0 + SE_BUTTON_SPACING / 320.0, 0.0 + SE_BUTTON_SPACING / 480.0},
};

static const NSInteger SE_NUM_GBA_BUTTONS = sizeof(SEGBAButtons) / sizeof(SEButtonLayout);

@interface SEController () {
    se_button_t g_pressedButtons[SE_NUM_BUTTONS];
    BOOL g_buttonState[SE_NUM_BUTTONS];
    CGRect g_buttonFrames[SE_NUM_BUTTONS];
    CGFloat g_buttonScales[SE_NUM_BUTTONS];
    se_system_t g_system;
    CGSize g_viewSize;
}

@end

@implementation SEController

- (instancetype)initWithSystem:(se_system_t)system {
    self = [super init];
    if (self) {
        g_system = system;
        g_viewSize = CGSizeMake(320, 480); // Default size
        
        // Initialize button states
        for (int i = 0; i < SE_NUM_BUTTONS; i++) {
            g_buttonState[i] = NO;
            g_buttonScales[i] = 1.0;
        }
        
        [self updateFrameWithSize:g_viewSize];
    }
    return self;
}

#pragma mark - Input Handling

- (void)handleTouch:(UITouch *)touch inView:(UIView *)view withType:(UITouchType)type {
    CGPoint location = [touch locationInView:view];
    
    // Convert to normalized coordinates
    CGFloat x = location.x / view.bounds.size.width;
    CGFloat y = location.y / view.bounds.size.height;
    
    // Find which button was touched
    for (int i = 0; i < SE_NUM_GBA_BUTTONS; i++) {
        if (CGRectContainsPoint(g_buttonFrames[SEGBAButtons[i].button], location)) {
            BOOL pressed = (type != UITouchTypeEnd && type != UITouchTypeCancel);
            [self setButton:SEGBAButtons[i].button pressed:pressed];
            break;
        }
    }
}

- (void)setButton:(se_button_t)button pressed:(BOOL)pressed {
    if (button >= SE_NUM_BUTTONS) return;
    
    g_buttonState[button] = pressed;
    g_buttonScales[button] = pressed ? 1.2 : 1.0;
    
    // Update SkyEmu input state
    // The actual input is read by sb_poll_controller_input in se_run_frame
}

- (void)setKey:(NSInteger)keyCode pressed:(BOOL)pressed {
    se_button_t button = [self buttonForKeyCode:keyCode];
    if (button != SE_NUM_BUTTONS) {
        [self setButton:button pressed:pressed];
    }
}

- (se_button_t)buttonForKeyCode:(NSInteger)keyCode {
    // Map common iOS keys to buttons
    switch (keyCode) {
        case 113: // A
            return SE_BUTTON_A;
        case 114: // B
            return SE_BUTTON_B;
        case 115: // X
            return SE_BUTTON_X;
        case 116: // Y
            return SE_BUTTON_Y;
        case 126: // Up
            return SE_BUTTON_UP;
        case 125: // Down
            return SE_BUTTON_DOWN;
        case 123: // Left
            return SE_BUTTON_LEFT;
        case 124: // Right
            return SE_BUTTON_RIGHT;
        case 12: // L
            return SE_BUTTON_L;
        default:
            return SE_NUM_BUTTONS;
    }
}

- (void)resetButtons {
    for (int i = 0; i < SE_NUM_BUTTONS; i++) {
        g_buttonState[i] = NO;
        g_buttonScales[i] = 1.0;
    }
}

- (BOOL)isButtonPressed:(se_button_t)button {
    if (button >= SE_NUM_BUTTONS) return NO;
    return g_buttonState[button];
}

- (NSArray<NSNumber *> *)getPressedButtons {
    NSMutableArray *pressed = [NSMutableArray array];
    for (int i = 0; i < SE_NUM_BUTTONS; i++) {
        if (g_buttonState[i]) {
            [pressed addObject:@(i)];
        }
    }
    return pressed;
}

#pragma mark - Layout

- (void)setControllerPosition:(CGFloat)x y:(CGFloat)y width:(CGFloat)width height:(CGFloat)height {
    g_viewSize = CGSizeMake(width, height);
    [self updateFrameWithSize:g_viewSize];
}

- (BOOL)point:(CGPoint)point isWithinButton:(se_button_t)button {
    if (button >= SE_NUM_BUTTONS) return NO;
    return CGRectContainsPoint(g_buttonFrames[button], point);
}

- (CGRect)getButtonFrame:(se_button_t)button {
    if (button >= SE_NUM_BUTTONS) return CGRectZero;
    return g_buttonFrames[button];
}

- (CGFloat)getButtonScale:(se_button_t)button {
    if (button >= SE_NUM_BUTTONS) return 1.0;
    return g_buttonScales[button];
}

- (void)updateFrameWithSize:(CGSize)size {
    g_viewSize = size;
    
    // Update button frames based on view size
    for (int i = 0; i < SE_NUM_GBA_BUTTONS; i++) {
        SEButtonLayout layout = SEGBAButtons[i];
        CGFloat btnX = layout.x * size.width;
        CGFloat btnY = layout.y * size.height;
        g_buttonFrames[layout.button] = CGRectMake(btnX, btnY, SE_BUTTON_SIZE, SE_BUTTON_SIZE);
    }
}

#pragma mark - Keyboard Input

- (void)keyDown:(NSEvent *)event {
    // macOS keyboard handling (if needed for simulator testing)
    NSUInteger keyCode = event.keyCode;
    [self setKey:(NSInteger)keyCode pressed:YES];
}

- (void)keyUp:(NSEvent *)event {
    NSUInteger keyCode = event.keyCode;
    [self setKey:(NSInteger)keyCode pressed:NO];
}

@end

#pragma mark - SEViewController Implementation

@interface SEViewController ()

@property (nonatomic, strong) CADisplayLink *displayLink;
@property (nonatomic, strong) UIView *renderView;

@end

@implementation SEViewController

- (instancetype)initWithSystem:(se_system_t)system {
    self = [super initWithNibName:nil bundle:nil];
    if (self) {
        g_system = system;
        self.controller = [[SEController alloc] initWithSystem:system];
        
        // Create render view
        self.renderView = [[UIView alloc] initWithFrame:[UIScreen mainScreen].bounds];
        self.renderView.backgroundColor = [UIColor blackColor];
        self.renderView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        
        // Setup display link for frame updates
        self.displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(renderFrame)];
        self.displayLink.preferredFramesPerSecond = 60;
        
        [self.view addSubview:self.renderView];
    }
    return self;
}

- (void)startEmulation {
    se_init(g_system, nil);
    [self.displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

- (void)stopEmulation {
    se_shutdown();
    [self.displayLink invalidate];
    self.displayLink = nil;
}

- (void)loadROMAtPath:(NSString *)path {
    const char *cPath = [path UTF8String];
    se_load_rom(cPath);
}

- (void)renderFrame {
    // Run one frame of emulation
    se_run_frame();
    
    // Update controller scale values
    for (int i = 0; i < SE_NUM_BUTTONS; i++) {
        if (i < SE_NUM_GBA_BUTTONS) {
            [self.controller getButtonScale:(se_button_t)i];
        }
    }
}

#pragma mark - Life Cycle

- (void)viewDidLayoutSubviews {
    [super viewDidLayoutSubviews];
    [self.controller updateFrameWithSize:self.view.bounds.size];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    // Configure for iOS
    if (@available(iOS 11.0, *)) {
        self.additionalSafeAreaInsets = UIEdgeInsetsZero;
    }
}

@end
