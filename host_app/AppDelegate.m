#import "AppDelegate.h"
#import "skyemu.h"          // public API of the static library
#import "sokol_app.h"        // Sokol iOS helpers

@implementation SkyEmuAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Obtain the Sokol description from the static library and initialise Sokol for iOS.
    sapp_desc desc = skyemu_sokol_desc();
    sapp_ios_init(&desc);

    // Create a window – required by UIKit even though Sokol draws into its own view.
    self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
    self.window.backgroundColor = [UIColor blackColor];
    [self.window makeKeyAndVisible];
    return YES;
}

// Forward UIApplication lifecycle events to Sokol – optional but recommended.
- (void)applicationWillResignActive:(UIApplication *)application {
    sapp_ios_event(SAPP_EVENTTYPE_APP_WILL_RESIGN_ACTIVE, NULL);
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    sapp_ios_event(SAPP_EVENTTYPE_APP_DID_BECOME_ACTIVE, NULL);
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Clean up the emulator before the process ends.
    skyemu_cleanup();
    sapp_ios_event(SAPP_EVENTTYPE_APP_WILL_TERMINATE, NULL);
}

@end
