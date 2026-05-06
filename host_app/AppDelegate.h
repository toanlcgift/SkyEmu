#import <UIKit/UIKit.h>

/**
 * SkyEmuAppDelegate – minimal UIApplicationDelegate that boots the SkyEmu static library.
 * This header is intended to be used in a Xamarin iOS Binding Library. The generated
 * binding will expose the Objective‑C class to C# as `SkyEmuAppDelegate`.
 */
@interface SkyEmuAppDelegate : UIResponder <UIApplicationDelegate>
@property (strong, nonatomic) UIWindow *window;
@end
