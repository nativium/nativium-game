// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#import <Foundation/Foundation.h>
@class NTVGameApplicationCore;


@interface NTVGameApplicationCore : NSObject

+ (nullable NTVGameApplicationCore *)shared;

- (nonnull NSString *)getVersion;

- (void)initialize:(int32_t)width
            height:(int32_t)height
              mode:(int32_t)mode;

@end
