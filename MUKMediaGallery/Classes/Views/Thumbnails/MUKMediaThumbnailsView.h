// Copyright (c) 2012, Marco Muccinelli
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// * Neither the name of the <organization> nor the
// names of its contributors may be used to endorse or promote products
// derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#import <UIKit/UIKit.h>
#import <MUKMediaGallery/MUKMediaAssetProtocol.h>
#import <MUKObjectCache/MUKObjectCache.h>
#import <MUKNetworking/MUKNetworking.h>

/**
 A view which displays a grid of thumbnails.
 */
@interface MUKMediaThumbnailsView : UIView
/** @name Properties */
/**
 Media assets.
 
 This an array of instances which conform to MUKMediaAsset protocol.
 */
@property (nonatomic, strong) NSArray *mediaAssets;
/**
 Cache where images are stored.
 
 This object is lazy loaded, but you can customize its behaviour.
 
 @warning You should set file cache handlers if you decide to cache thumbnails
 to file.
 */
@property (nonatomic, strong) MUKObjectCache *thumbnailImageCache;
/**
 Cache thumbnail images to file.
 
 Default is `NO`. If `YES`, thumbnails are searched/saved in file cache too.
 
 @warning You should set thumbnailImageCache file cache handlers if you decide
 to cache thumbnails to file.
 */
@property (nonatomic) BOOL usesThumbnailImageFileCache;
/**
 Connection queue where thumbnails are downloaded.
 */
@property (nonatomic, strong, readonly) MUKURLConnectionQueue *thumbnailDownloadQueue;
/**
 Size of thumbnails.
 
 Default is `{79, 79}`.
 */
@property (nonatomic) CGSize thumbnailSize;
/**
 Space between thumbnails.
 
 Default is `{4, 4}`.
 */
@property (nonatomic) CGSize thumbnailOffset;
/**
 Top padding over the thumbnails.
 
 This is useful when you put this view into a navigation controller with
 transparent navigation bar.
 
    CGFloat statusBarHeight;
    if (UIInterfaceOrientationIsPortrait([[UIApplication sharedApplication] statusBarOrientation])) 
    {
       statusBarHeight = [[UIApplication sharedApplication] statusBarFrame].size.height;
    }
    else {
       statusBarHeight = [[UIApplication sharedApplication] statusBarFrame].size.width;
    }
 
    CGFloat topPadding = statusBarHeight + self.navigationController.navigationBar.frame.size.height;
 */
@property (nonatomic) CGFloat topPadding;
/**
 Displays media asset count under thumbnails.
 
 This count is displayed only if there media assets in mediaAssets array.
 
 Default is `YES`.
 */
@property (nonatomic) BOOL displaysMediaAssetsCount;

/** @name Handlers */
/**
 */
@property (nonatomic, copy) NSURLRequest* (^thumbnailDownloadRequestHandler)(id<MUKMediaAsset> mediaAsset);

/** @name Methods */
/**
 Reload thumbnail cells.
 */
- (void)reloadThumbnails;
@end


@interface MUKMediaThumbnailsView (ThumbnailDownload)
/**
 Create URL request to download thumbnail image.
 
 Default implementation calls thumbnailDownloadRequestHandler. If handler is 
 not set or it returns `nil`, this method returns a standard URL request with
 [MUKMediaAsset mediaThumbnailURL].
 */
- (NSURLRequest *)requestForMediaAsset:(id<MUKMediaAsset>)mediaAsset;
@end

