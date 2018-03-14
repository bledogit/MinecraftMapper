//
//  ViewController.h
//  MineMapper
//
//  Created by Jose on 6/10/15.
//  Copyright (c) 2015 Jose. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface ViewController : NSViewController

@property (weak) IBOutlet NSImageView* canvas;
@property (weak) IBOutlet NSTextField* coordenates;
@property (weak) IBOutlet NSProgressIndicator* progress;
@property (weak) IBOutlet NSScrollView* scrolledCanvas;
@property NSString*  path;




- (void) performLoadMap: (int) type;
- (void) performTestMap;
- (void)zoom: (double)factor;
- (void)zoomIn;
- (void)zoomOut;


@end



