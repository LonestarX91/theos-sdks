//
//  ALAssetsLibrary.h
//  AssetsLibrary
//
//  Copyright 2010 Apple Inc. All rights reserved.
//
/*
 *
 * This class represents the set of all videos and photos that are under the control of the Photos application. This includes
 * those that are in the saved photos album and those coming from iTunes.
 * It is used to retrieve the list of all asset groups and to save images and videos into the Saved Photos album.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED

@class ALAsset;
@class ALAssetsGroup;

typedef NS_ENUM(NSInteger, ALAssetOrientation) {
    ALAssetOrientationUp NS_ENUM_DEPRECATED_IOS(4_0, 9_0),            // default orientation
    ALAssetOrientationDown NS_ENUM_DEPRECATED_IOS(4_0, 9_0),          // 180 deg rotation
    ALAssetOrientationLeft NS_ENUM_DEPRECATED_IOS(4_0, 9_0),          // 90 deg CCW
    ALAssetOrientationRight NS_ENUM_DEPRECATED_IOS(4_0, 9_0),         // 90 deg CW
    ALAssetOrientationUpMirrored NS_ENUM_DEPRECATED_IOS(4_0, 9_0),    // as above but image mirrored along other axis. horizontal flip
    ALAssetOrientationDownMirrored NS_ENUM_DEPRECATED_IOS(4_0, 9_0),  // horizontal flip
    ALAssetOrientationLeftMirrored NS_ENUM_DEPRECATED_IOS(4_0, 9_0),  // vertical flip
    ALAssetOrientationRightMirrored NS_ENUM_DEPRECATED_IOS(4_0, 9_0), // vertical flip
} NS_DEPRECATED_IOS(4_0, 9_0, "Use UIImageOrientation in the Photos framework instead");

enum {
    ALAssetsGroupLibrary     NS_ENUM_DEPRECATED_IOS(4_0, 9_0) = (1 << 0),         // The Library group that includes all assets.
    ALAssetsGroupAlbum       NS_ENUM_DEPRECATED_IOS(4_0, 9_0) = (1 << 1),         // All the albums synced from iTunes or created on the device.
    ALAssetsGroupEvent       NS_ENUM_DEPRECATED_IOS(4_0, 9_0) = (1 << 2),         // All the events synced from iTunes.
    ALAssetsGroupFaces       NS_ENUM_DEPRECATED_IOS(4_0, 9_0) = (1 << 3),         // All the faces albums synced from iTunes.
    ALAssetsGroupSavedPhotos NS_ENUM_DEPRECATED_IOS(4_0, 9_0) = (1 << 4),         // The Saved Photos album.
#if __IPHONE_5_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ALAssetsGroupPhotoStream NS_ENUM_DEPRECATED_IOS(5_0, 9_0) = (1 << 5),         // The PhotoStream album.
#endif
    ALAssetsGroupAll         NS_ENUM_DEPRECATED_IOS(4_0, 9_0) = 0xFFFFFFFF,       // The same as ORing together all the available group types,
};
typedef NSUInteger ALAssetsGroupType NS_DEPRECATED_IOS(4_0, 9_0, "Use PHAssetCollectionType and PHAssetCollectionSubtype in the Photos framework instead");

typedef NS_ENUM(NSInteger, ALAuthorizationStatus) {
    ALAuthorizationStatusNotDetermined NS_ENUM_DEPRECATED_IOS(6_0, 9_0) = 0, // User has not yet made a choice with regards to this application
    ALAuthorizationStatusRestricted NS_ENUM_DEPRECATED_IOS(6_0, 9_0),        // This application is not authorized to access photo data.
                                            // The user cannot change this application’s status, possibly due to active restrictions
                                            //  such as parental controls being in place.
    ALAuthorizationStatusDenied NS_ENUM_DEPRECATED_IOS(6_0, 9_0),            // User has explicitly denied this application access to photos data.
    ALAuthorizationStatusAuthorized NS_ENUM_DEPRECATED_IOS(6_0, 9_0)        // User has authorized this application to access photos data.
} NS_DEPRECATED_IOS(6_0, 9_0, "Use PHAuthorizationStatus in the Photos framework instead");


// This block is executed when a match is found during enumeration. The match is passed to the block in the group argument.
// When the enumeration is done, the block will be called with group set to nil.
// Setting the output argument stop to YES will finish the enumeration.
typedef void (^ALAssetsLibraryGroupsEnumerationResultsBlock)(ALAssetsGroup *group, BOOL *stop) NS_DEPRECATED_IOS(4_0, 9_0, "Use the PHFetchResult returned by fetchAssetCollectionsInCollectionList:options: on PHAssetCollection from the Photos framework to enumerate the asset collections in a collection list instead");

// This block is executed if the user has granted access to the caller to access the data managed by the framework.
// If the asset is not found, asset is nil.
typedef void (^ALAssetsLibraryAssetForURLResultBlock)(ALAsset *asset) NS_DEPRECATED_IOS(4_0, 9_0, "Use fetchAssetsWithLocalIdentifiers:options: on PHAsset to fetch assets by local identifier (or to lookup PHAssets by a previously known ALAssetPropertyAssetURL use fetchAssetsWithALAssetURLs:options:) from the Photos framework instead");

// This block is executed if the user has granted access to the caller to access the data managed by the framework.
// If the group is not found, group is nil.
typedef void (^ALAssetsLibraryGroupResultBlock)(ALAssetsGroup *group) NS_DEPRECATED_IOS(5_0, 9_0, "Use fetchAssetCollectionsWithLocalIdentifiers:options: on PHAssetCollection to fetch the asset collections by local identifier (or to lookup PHAssetCollections by a previously known ALAssetsGroupPropertyURL use fetchAssetCollectionsWithALAssetGroupURLs:options:) from the Photos framework instead");

// This block is executed if the user does not grant access to the caller to access the data managed by the framework or if the data is currently unavailable.
typedef void (^ALAssetsLibraryAccessFailureBlock)(NSError *error) NS_DEPRECATED_IOS(4_0, 9_0, "Use the Photos framework instead");

// This block is executed when saving an image by -writeImageToSavedPhotosAlbum:completionBlock: finishes. The assetURL can later be used to reference the saved image.
typedef void (^ALAssetsLibraryWriteImageCompletionBlock)(NSURL *assetURL, NSError *error) NS_DEPRECATED_IOS(4_0, 9_0, "Use performChanges:completionHandler: or performChangesAndWait: on the shared PHPhotoLibrary with a PHAssetChangeRequest from the Photos framework instead");
// This block is executed when saving a video by -writeVideoAtPathToSavedPhotosAlbum:completionBlock: finishes. The assetURL can later be used to reference the saved video.
typedef void (^ALAssetsLibraryWriteVideoCompletionBlock)(NSURL *assetURL, NSError *error) NS_DEPRECATED_IOS(4_0, 9_0, "Use performChanges:completionHandler: or performChangesAndWait: on the shared PHPhotoLibrary with a PHAssetChangeRequest from the Photos framework instead");


NS_CLASS_DEPRECATED_IOS(4_0, 9_0, "Use PHPhotoLibrary from the Photos framework instead")
@interface ALAssetsLibrary : NSObject {
@package
    id _internal;
    
}

// Get the list of groups that match the given types. Multiple types can be ORed together. The results are passed one by one to the caller by executing the enumeration block.
// When the enumeration is done, 'enumerationBlock' will be called with group set to nil.
// When groups are enumerated, the user may be asked to confirm the application's access to the data. If the user denies access to the application or if no application is allowed to access the data, the failure block will be called.
// If the data is currently unavailable, the failure block will be called.
- (void)enumerateGroupsWithTypes:(ALAssetsGroupType)types usingBlock:(ALAssetsLibraryGroupsEnumerationResultsBlock)enumerationBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock NS_DEPRECATED_IOS(4_0, 9_0, "Use the PHFetchResult returned by one of the fetch... methods on PHAssetCollection from the Photos framework to enumerate asset collections instead");

// Returns an ALAsset object in the result block for a URL previously retrieved from an ALAsset object.
// When the ALAsset is requested, the user may be asked to confirm the application's access to the data. If the user denies access to the application or if no application is allowed to access the data, the failure block will be called.
// If the data is currently unavailable, the failure block will be called.
- (void)assetForURL:(NSURL *)assetURL resultBlock:(ALAssetsLibraryAssetForURLResultBlock)resultBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock NS_DEPRECATED_IOS(4_0, 9_0, "Use fetchAssetsWithLocalIdentifiers:options: on PHAsset to fetch assets by local identifier (or to lookup PHAssets by a previously known ALAssetPropertyAssetURL use fetchAssetsWithALAssetURLs:options:) from the Photos framework instead");

// Returns an ALAssetsGroup object in the result block for a URL previously retrieved from an ALAssetsGroup object.
// When the ALAssetsGroup is requested, the user may be asked to confirm the application's access to the data.  If the user denies access to the application or if no application is allowed to access the data, the failure block will be called.
// If the data is currently unavailable, the failure block will be called.
- (void)groupForURL:(NSURL *)groupURL resultBlock:(ALAssetsLibraryGroupResultBlock)resultBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock NS_DEPRECATED_IOS(5_0, 9_0, "Use fetchAssetCollectionsWithLocalIdentifiers:options: on PHAssetCollection to fetch the asset collections by local identifier (or to lookup PHAssetCollections by a previously known ALAssetsGroupPropertyURL use fetchAssetCollectionsWithALAssetGroupURLs:options:) from the Photos framework instead");

// Add a new ALAssetsGroup to the library.
// The name of the ALAssetsGroup is name and the type is ALAssetsGroupAlbum.  The editable property of this ALAssetsGroup returns YES.
// If name conflicts with another ALAssetsGroup with the same name, then the group is not created and the result block returns a nil group.
// When the ALAssetsGroup is added, the user may be asked to confirm the application's access to the data.  If the user denies access to the application or if no application is allowed to access the data, the failure block will be called.
// If the data is currently unavailable, the failure block will be called.
- (void)addAssetsGroupAlbumWithName:(NSString *)name resultBlock:(ALAssetsLibraryGroupResultBlock)resultBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock NS_DEPRECATED_IOS(5_0, 9_0, "Use creationRequestForAssetCollectionWithTitle: on PHAssetCollectionChangeRequest from the Photos framework to create a new asset collection instead");

// These methods can be used to add photos or videos to the saved photos album.

// With a UIImage, the API user can use -[UIImage CGImage] to get a CGImageRef, and cast -[UIImage imageOrientation] to ALAssetOrientation.
- (void)writeImageToSavedPhotosAlbum:(CGImageRef)imageRef orientation:(ALAssetOrientation)orientation completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock NS_DEPRECATED_IOS(4_0, 9_0, "Use creationRequestForAssetFromImage: on PHAssetChangeRequest from the Photos framework to create a new asset instead");

// The API user will have to specify the orientation key in the metadata dictionary to preserve the orientation of the image
- (void)writeImageToSavedPhotosAlbum:(CGImageRef)imageRef metadata:(NSDictionary *)metadata completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock NS_DEPRECATED_IOS(4_1, 9_0, "Use creationRequestForAssetFromImage: on PHAssetChangeRequest from the Photos framework to create a new asset instead");

// If there is a conflict between the metadata in the image data and the metadata dictionary, the image data metadata values will be overwritten
- (void)writeImageDataToSavedPhotosAlbum:(NSData *)imageData metadata:(NSDictionary *)metadata completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock NS_DEPRECATED_IOS(4_1, 9_0, "Use creationRequestForAssetFromImageData: on PHAssetChangeRequest from the Photos framework to create a new asset instead");

- (void)writeVideoAtPathToSavedPhotosAlbum:(NSURL *)videoPathURL completionBlock:(ALAssetsLibraryWriteVideoCompletionBlock)completionBlock NS_DEPRECATED_IOS(4_0, 9_0, "Use creationRequestForAssetFromVideoAtFilePath: on PHAssetChangeRequest from the Photos framework to create a new asset instead");
- (BOOL)videoAtPathIsCompatibleWithSavedPhotosAlbum:(NSURL *)videoPathURL NS_DEPRECATED_IOS(5_0, 9_0);

// Returns photo data authorization status for this application
+ (ALAuthorizationStatus)authorizationStatus NS_DEPRECATED_IOS(6_0, 9_0, "Use authorizationStatus on the shared PHPhotoLibrary from the Photos framework instead");

// Disable retrieval and notifications for Shared Photo Streams
+ (void)disableSharedPhotoStreamsSupport NS_DEPRECATED_IOS(6_0, 9_0, "Use the Photos framework instead");

@end

// Notifications

// This notification will be sent when the contents of the ALAssetsLibrary have changed from under the app that is using the data.
// The API user should retain the library object to receive this notification.
// The userInfo may include the keys listed below, which identify specific ALAssets or ALAssetGroups that have become invalid and should be discarded. The values are NSSets of NSURLs which match the ALAssetPropertyURL and ALAssetsGroupPropertyURL properties. 
// If the userInfo is nil, all ALAssets and ALAssetGroups should be considered invalid and discarded.
// Modified ALAssets will be identified by the ALAssetLibraryUpdatedAssetsKey, but inserted or deleted ALAssets are identified by invalidating the containing ALAssetGroups.
extern NSString *const ALAssetsLibraryChangedNotification NS_DEPRECATED_IOS(4_0, 9_0, "Use photoLibraryDidChange: notification from the Photos framework instead");

extern NSString *const ALAssetLibraryUpdatedAssetsKey NS_DEPRECATED_IOS(6_0, 9_0, "Use changeDetailsForFetchResult: and changeDetailsForObject: to get change details via the PHChange object included on photoLibraryDidChange: from the Photos framework instead");
extern NSString *const ALAssetLibraryInsertedAssetGroupsKey NS_DEPRECATED_IOS(6_0, 9_0, "Use changeDetailsForFetchResult: and changeDetailsForObject: to get change details via the PHChange object included on photoLibraryDidChange: from the Photos framework instead");
extern NSString *const ALAssetLibraryUpdatedAssetGroupsKey NS_DEPRECATED_IOS(6_0, 9_0, "Use changeDetailsForFetchResult: and changeDetailsForObject: to get change details via the PHChange object included on photoLibraryDidChange: from the Photos framework instead");
extern NSString *const ALAssetLibraryDeletedAssetGroupsKey NS_DEPRECATED_IOS(6_0, 9_0, "Use changeDetailsForFetchResult: and changeDetailsForObject: to get change details via the PHChange object included on photoLibraryDidChange: from the Photos framework instead");

// Errors

// Constant used by NSError to distinguish errors belonging to the AssetsLibrary domain
extern NSString *const ALAssetsLibraryErrorDomain NS_DEPRECATED_IOS(4_0, 9_0, "Use the Photos framework instead");

// AssetsLibrary-related error codes
enum {
    ALAssetsLibraryUnknownError =                 -1,      // Error (reason unknown)
    
    // These errors would be returned in the ALAssetsLibraryWriteImageCompletionBlock and ALAssetsLibraryWriteVideoCompletionBlock completion blocks,
    // as well as in the completion selector for UIImageWriteToSavedPhotosAlbum() and UISaveVideoAtPathToSavedPhotosAlbum()
    ALAssetsLibraryWriteFailedError =           -3300,      // Write error (write failed)
    ALAssetsLibraryWriteBusyError =             -3301,      // Write error (writing is busy, try again)
    ALAssetsLibraryWriteInvalidDataError =      -3302,      // Write error (invalid data)
    ALAssetsLibraryWriteIncompatibleDataError = -3303,      // Write error (incompatible data)
    ALAssetsLibraryWriteDataEncodingError =     -3304,      // Write error (data has invalid encoding)
    ALAssetsLibraryWriteDiskSpaceError =        -3305,      // Write error (out of disk space)

    // This error would be returned in the ALAssetsLibraryAccessFailureBlock, ALAssetsLibraryWriteImageCompletionBlock, and ALAssetsLibraryWriteVideoCompletionBlock completion blocks,
    // as well as in the completion selector for UIImageWriteToSavedPhotosAlbum() and UISaveVideoAtPathToSavedPhotosAlbum()
    ALAssetsLibraryDataUnavailableError =       -3310,      // Data unavailable (data currently unavailable)    
    
    // These errors would be returned in the ALAssetsLibraryAccessFailureBlock
    ALAssetsLibraryAccessUserDeniedError =      -3311,      // Access error (user denied access request)
    ALAssetsLibraryAccessGloballyDeniedError =  -3312,      // Access error (access globally denied)
} NS_DEPRECATED_IOS(4_0, 9_0, "Use the Photos framework instead");

#endif
