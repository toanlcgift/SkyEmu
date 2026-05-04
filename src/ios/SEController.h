/*
 *  SEController.h
 *  SkyEmu iOS Controller
 *
 *  Objective-C wrapper for emulator input
 */

#import <UIKit/UIKit.h>
#import "SkyEmu.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * SkyEmu Controller
 * Handles input from touch, keyboard, and gamepad
 */
@interface SEController : NSObject

/**
 * Initialize controller with specified system
 * @param system System type (GB, GBA, or NDS)
 */
- (instancetype)initWithSystem:(se_system_t)system;

/**
 * Handle touch input
 * @param touch UITouch object
 * @param view View where touch occurred
 * @param type Touch type (began, moved, ended, cancelled)
 */
- (void)handleTouch:(UITouch *)touch inView:(UIView *)view withType:(UITouchType)type;

/**
 * Handle button press/release
 * @param button Button to press/release
 * @param pressed YES if pressed, NO if released
 */
- (void)setButton:(se_button_t)button pressed:(BOOL)pressed;

/**
 * Handle keyboard input
 * @param keyCode Virtual key code
 * @param pressed YES if pressed, NO if released
 */
- (void)setKey:(NSInteger)keyCode pressed:(BOOL)pressed;

/**
 * Reset all buttons to released state
 */
- (void)resetButtons;

/**
 * Get button state
 * @param button Button to check
 * @return YES if button is pressed
 */
- (BOOL)isButtonPressed:(se_button_t)button;

/**
 * Get all button states
 * @return Array of pressed button indices
 */
- (NSArray<NSNumber *> *)getPressedButtons;

/**
 * Set controller position (for on-screen controller)
 * @param x X position (0.0 to 1.0)
 * @param y Y position (0.0 to 1.0)
 * @param width Button width
 * @param height Button height
 */
- (void)setControllerPosition:(CGFloat)x y:(CGFloat)y width:(CGFloat)width height:(CGFloat)height;

/**
 * Check if point is within button area
 * @param point Point in view coordinates
 * @param button Button index
 * @return YES if point is within button area
 */
- (BOOL)point:(CGPoint)point isWithinButton:(se_button_t)button;

/**
 * Get button frame in view coordinates
 * @param button Button index
 * @return CGRect for button
 */
- (CGRect)getButtonFrame:(se_button_t)button;

/**
 * Get current button scale factor (for touch feedback)
 * @param button Button index
 * @return Scale factor (1.0 = normal, >1.0 = pressed)
 */
- (CGFloat)getButtonScale:(se_button_t)button;

/**
 * Update frame with new view size
 * @param size New view size
 */
- (void)updateFrameWithSize:(CGSize)size;

@end

/**
 * SEViewController
 * Base view controller for SkyEmu with controller support
 */
@interface SEViewController : UIViewController

/**
 * SkyEmu controller
 */
@property (nonatomic, strong) SEController *controller;

/**
 * Render view
 */
@property (nonatomic, strong) UIView *renderView;

/**
 * Initialize with system
 * @param system System type
 */
- (instancetype)initWithSystem:(se_system_t)system NS_DESIGNATED_INITIALIZER;

/**
 * Start SkyEmu emulation
 */
- (void)startEmulation;

/**
 * Stop SkyEmu emulation
 */
- (void)stopEmulation;

/**
 * Load ROM file
 * @param path Path to ROM file
 */
- (void)loadROMAtPath:(NSString *)path;

/**
 * Handle frame rendering
 * Call this from your view's drawRect or render loop
 */
- (void)renderFrame;

@end

NS_ASSUME_NONNULL_END
