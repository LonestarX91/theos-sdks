//
//  MTLSampler.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLDevice.h>
#import <Metal/MTLDepthStencil.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 @enum MTLSamplerMinMagFilter
 @abstract Options for filtering texels within a mip level.
 
 @constant MTLSamplerMinMagFilterNearest
 Select the single texel nearest to the sample point.
 
 @constant MTLSamplerMinMagFilterLinear
 Select two texels in each dimension, and interpolate linearly between them.  Not all devices support linear filtering for all formats.  Integer textures can not use linear filtering on any device, and only some devices support linear filtering of Float textures.
 */
typedef NS_ENUM(NSUInteger, MTLSamplerMinMagFilter) {
    MTLSamplerMinMagFilterNearest = 0,
    MTLSamplerMinMagFilterLinear = 1,
} NS_ENUM_AVAILABLE(10_11, 8_0);

/*!
 @enum MTLSamplerMipFilter
 @abstract Options for selecting and filtering between mipmap levels
 @constant MTLSamplerMipFilterNotMipmapped The texture is sampled as if it only had a single mipmap level.  All samples are read from level 0.
 @constant MTLSamplerMipFilterNearest The nearst mipmap level is selected.
 @constant MTLSamplerMipFilterLinear If the filter falls between levels, both levels are sampled, and their results linearly interpolated between levels.
 */
typedef NS_ENUM(NSUInteger, MTLSamplerMipFilter) {
    MTLSamplerMipFilterNotMipmapped = 0,
    MTLSamplerMipFilterNearest = 1,
    MTLSamplerMipFilterLinear = 2,
} NS_ENUM_AVAILABLE(10_11, 8_0);

/*!
 @enum MTLSamplerAddressMode
 @abstract Options for what value is returned when a fetch falls outside the bounds of a texture.
 
 @constant MTLSamplerAddressModeClampToEdge
 Texture coordinates will be clamped between 0 and 1.

 @constant MTLSamplerAddressModeMirrorClampToEdge
 Mirror the texture while coordinates are within -1..1, and clamp to edge when outside.

 @constant MTLSamplerAddressModeRepeat
 Wrap to the other side of the texture, effectively ignoring fractional parts of the texture coordinate.
 
 @constant MTLSamplerAddressModeMirrorRepeat
 Between -1 and 1 the texture is mirrored across the 0 axis.  The image is repeated outside of that range.
 
 @constant MTLSamplerAddressModeClampToZero
 ClampToZero returns transparent zero (0,0,0,0) for images with an alpha channel, and returns opaque zero (0,0,0,1) for images without an alpha channel.
 */
typedef NS_ENUM(NSUInteger, MTLSamplerAddressMode) {
    MTLSamplerAddressModeClampToEdge = 0,
    MTLSamplerAddressModeMirrorClampToEdge NS_AVAILABLE_MAC(10_11) = 1,
    MTLSamplerAddressModeRepeat = 2,
    MTLSamplerAddressModeMirrorRepeat = 3,
    MTLSamplerAddressModeClampToZero = 4,
} NS_ENUM_AVAILABLE(10_11, 8_0);

/*!
 @class MTLSamplerDescriptor
 @abstract A mutable descriptor used to configure a sampler.  When complete, this can be used to create an immutable MTLSamplerState.
 */
NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLSamplerDescriptor : NSObject <NSCopying>

/*!
 @property minFilter
 @abstract Filter option for combining texels within a mipmap level the sample footprint is larger than a pixel (minification).
 @discussion The default value is MTLSamplerMinMagFilterNearest.
 */
@property (nonatomic) MTLSamplerMinMagFilter minFilter;

/*!
 @property magFilter
 @abstract Filter option for combining texels within a mipmap level the sample footprint is smaller than a pixel (magnification).
 @discussion The default value is MTLSamplerMinMagFilterNearest.
 */
@property (nonatomic) MTLSamplerMinMagFilter magFilter;

/*!
 @property mipFilter
 @abstract Filter options for filtering between two mipmap levels.
 @discussion The default value is MTLSamplerMipFilterNotMipmapped
 */
@property (nonatomic) MTLSamplerMipFilter mipFilter;

/*!
 @property maxAnisotropy
 @abstract The number of samples that can be taken to improve quality of sample footprints that are anisotropic.
 @discussion The default value is 1.
 */
@property (nonatomic) NSUInteger maxAnisotropy;

/*!
 @property sAddressMode
 @abstract Set the wrap mode for the S texture coordinate.  The default value is MTLSamplerAddressModeClampToEdge.
 */
@property (nonatomic) MTLSamplerAddressMode sAddressMode;

/*!
 @property tAddressMode
 @abstract Set the wrap mode for the T texture coordinate.  The default value is MTLSamplerAddressModeClampToEdge.
 */
@property (nonatomic) MTLSamplerAddressMode tAddressMode;

/*!
 @property rAddressMode
 @abstract Set the wrap mode for the R texture coordinate.  The default value is MTLSamplerAddressModeClampToEdge.
 */
@property (nonatomic) MTLSamplerAddressMode rAddressMode;

/*!
 @property normalizedCoordinates.
 @abstract If YES, texture coordates are from 0 to 1.  If NO, texture coordinates are 0..width, 0..height.
 @discussion normalizedCoordinates defaults to YES.  Non-normalized coordinates should only be used with 1D and 2D textures with the ClampToEdge wrap mode, otherwise the results of sampling are undefined.
 */
@property (nonatomic) BOOL normalizedCoordinates;

/*!
 @property lodMinClamp
 @abstract The minimum level of detail that will be used when sampling from a texture.
 @discussion The default value of lodMinClamp is 0.0.  Clamp values are ignored for texture sample variants that specify an explicit level of detail.
 */
@property (nonatomic) float lodMinClamp;

/*!
 @property lodMaxClamp
 @abstract The maximum level of detail that will be used when sampling from a texture.
 @discussion The default value of lodMaxClamp is FLT_MAX.  Clamp values are ignored for texture sample variants that specify an explicit level of detail.
 */
@property (nonatomic) float lodMaxClamp;

/*!
 @property lodAverage
 @abstract If YES, an average level of detail will be used when sampling from a texture. If NO, no averaging is performed.
 @discussion lodAverage defaults to NO. This option is a performance hint. An implementation is free to ignore this property.
 */
@property (nonatomic) BOOL lodAverage NS_AVAILABLE_IOS(9_0);

/*!
 @property compareFunction
 @abstract Set the comparison function used when sampling shadow maps. The default value is MTLCompareFunctionNever.
 */
@property (nonatomic) MTLCompareFunction compareFunction NS_AVAILABLE(10_11, 9_0);

/*!
 @property label
 @abstract A string to help identify the created object.
 */
@property (nullable, copy, nonatomic) NSString *label;

@end

/*!
 @protocol MTLSamplerState
 @abstract An immutable collection of sampler state compiled for a single device.
 */
NS_AVAILABLE(10_11, 8_0)
@protocol MTLSamplerState <NSObject>

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, readonly) NSString *label;

/*!
 @property device
 @abstract The device this resource was created against.  This resource can only be used with this device.
 */
@property (readonly) id <MTLDevice> device;

@end
NS_ASSUME_NONNULL_END