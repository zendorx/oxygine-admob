#include "iosAdmob.h"
#import <Foundation/Foundation.h>

/*void iosFacebookLogin()
{
    FBSDKLoginManager *login = [[FBSDKLoginManager alloc] init];
    [login
     logInWithReadPermissions: @[@"public_profile"]
     fromViewController:0
     handler:^(FBSDKLoginManagerLoginResult *result, NSError *error) {
         if (error) {
             NSLog(@"Process error");
         } else if (result.isCancelled) {
             NSLog(@"Cancelled");
         } else {
             NSLog(@"Logged in");
         }
     }];
}

std::string iosFacebookGetAccessToken()
{
    return [[FBSDKAccessToken currentAccessToken ].tokenString UTF8String];
}*/