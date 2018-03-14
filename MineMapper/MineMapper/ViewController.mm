//
//  ViewController.m
//  MineMapper
//
//  Created by Jose on 6/10/15.
//  Copyright (c) 2015 Jose. All rights reserved.
//

#import "ViewController.h"

#include "McpeHandler.h"

@implementation ViewController {
    int width;
    int height;
    double zoom_factor;
    NSPoint mapCenter;
    NSPoint downPos;
    NSPoint upPos;
    NSSize  selsize;
    NSTrackingArea* trackingArea;
    McpeHandler* mapxx;
}

@synthesize canvas;
@synthesize path;


- (void)viewDidLoad {
    [super viewDidLoad];
    zoom_factor = 1.0;
    
    trackingArea = [[NSTrackingArea alloc] initWithRect:  self.scrolledCanvas.frame
                    options:(NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingActiveAlways)
                    owner: self userInfo: nil];
    
    
    [self.scrolledCanvas addTrackingArea: trackingArea];
    
    // Do any additional setup after loading the view.
    
    
}

- (void) onResize {
    [self.scrolledCanvas removeTrackingArea:trackingArea];
    trackingArea = [[NSTrackingArea alloc] initWithRect:  self.scrolledCanvas.frame
                                                options:(NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingActiveAlways)
                                                  owner: self userInfo: nil];
    
    
    [self.scrolledCanvas addTrackingArea: trackingArea];
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

void updateProgress (int progress, void* context) {
    
    ViewController* controller = (__bridge ViewController*)context;
    static int lastprogress;
    
    if (lastprogress !=progress) {
    //dispatch_async(dispatch_get_main_queue(), ^{
    [controller.progress setDoubleValue:progress] ;
        
    //});
    NSLog(@"progress %d", progress);
        lastprogress = progress;
    }
}


- (void)updateMapImage: (const char*) bytes: (int) length {
    
    
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, bytes, length, NULL);
    
    CGColorSpaceRef space = CGColorSpaceCreateDeviceRGB();
    
    CGImageRef iref = CGImageCreate(width,
                                    height,
                                    8,
                                    32,
                                    width*4,
                                    space,
                                    kCGBitmapByteOrder32Little | kCGImageAlphaFirst,
                                    provider,
                                    NULL,
                                    YES,
                                    kCGRenderingIntentDefault);

    CGDataProviderRelease(provider);
    
    CGColorSpaceRelease(space);
   
    NSImage *image = [[NSImage alloc] initWithCGImage: iref size: NSMakeSize(width, height)];
    
    self.canvas.frame = NSMakeRect(0.0,0.0,width,height);
    self.canvas.bounds = NSMakeRect(0.0,0.0,width,height);
    self.canvas.image  = image;
    
    self.scrolledCanvas.documentView = self.canvas;
    
    
}


- (void)performLoadMap: (int) type {
    NSLog(@"Load Map url %@", path);


    
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{

        McpeHandler *h = new McpeHandler();

        h->setProgressHanler(updateProgress, (__bridge void*)self);
        
        h->loadLevelDB([path UTF8String]);
        
        h->findSizes();
        
        h->loadMap((MapType)type);
        
        width = h->getBitmapWidth();
        height = h->getBitmapHeight();
        mapCenter.x = h->getOffsetW();
        mapCenter.y = h->getOffsetH();
        
        const char* bytes = h->getBitmap();
        int length = width*height*4;
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [self updateMapImage:bytes : length];
            
        });
        
        delete h;
    });
    
    
}

- (void)performTestMap {
    NSLog(@"Load Map url %@", path);
    
    McpeHandler *h = new McpeHandler();
    
    h->testMap(64,48);
    
    width = h->getBitmapWidth();
    height = h->getBitmapHeight();
    mapCenter.x = h->getOffsetW();
    mapCenter.y = h->getOffsetH();
    
    const char* bytes = h->getBitmap();
    
    int length = width*height*4;
    
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, bytes, length, NULL);
    CGColorSpaceRef space = CGColorSpaceCreateDeviceRGB();
    
    CGImageRef iref = CGImageCreate(width,
                                    height,
                                    8,
                                    32,
                                    width*4,
                                    space,
                                    kCGBitmapByteOrder32Little | kCGImageAlphaFirst,
                                    provider,
                                    NULL,
                                    YES,
                                    kCGRenderingIntentDefault);
    
    CGDataProviderRelease(provider);
    CGColorSpaceRelease(space);
    
    NSImage *image = [[NSImage alloc] initWithCGImage: iref size: NSMakeSize(width, height)];
    NSRect imageRect        = NSMakeRect(0.0,0.0,width,height);

    
    self.canvas.frame = imageRect;
    self.canvas.bounds = imageRect;
    self.canvas.image  = image;

    self.scrolledCanvas.documentView = self.canvas;

    NSLog(@"Map Size: (%d %d)", (int)width, (int)height);
    
    delete h;
}

- (void)zoomIn {
    [self zoom: zoom_factor*2.0];
}

- (void)zoomOut {
    [self zoom: zoom_factor/2.0];
}

- (void)zoom: (double)factor {
    zoom_factor = factor;

    
    if (zoom_factor > self.scrolledCanvas.maxMagnification)
        zoom_factor = self.scrolledCanvas.maxMagnification;
  
    
    if (zoom_factor < self.scrolledCanvas.minMagnification)
        zoom_factor = self.scrolledCanvas.minMagnification;
   
    NSLog(@"Zoom factor %f", factor);
    
    self.scrolledCanvas.magnification = zoom_factor;
    
    
    
}

- (NSPoint ) convert: (NSPoint) mouseLoc {
    mouseLoc = [self.scrolledCanvas convertPoint:mouseLoc fromView: nil];
    mouseLoc = [self.canvas convertPoint: mouseLoc fromView: self.scrolledCanvas];
    
    mouseLoc.x = mouseLoc.x/16.0 - mapCenter.x;
    mouseLoc.y = (height - mouseLoc.y)/16.0 - mapCenter.y;
    
    return mouseLoc;
}

-(void)mouseDragged:(NSEvent *)theEvent {

    NSPoint mouseLoc = [self convert:[theEvent locationInWindow]];

    selsize.width = fabs(mouseLoc.x - downPos.x);
    selsize.height = fabs (mouseLoc.y - downPos.y);

    [self mouseMoved: theEvent];
}

-(void)mouseMoved:(NSEvent *)theEvent {
    
    NSPoint mouseLoc = [self convert:[theEvent locationInWindow]];
    
    [self.coordenates setStringValue: [NSString
                stringWithFormat: @"%.1f, %.1f    Rectangle: %.1f, %.1f   Zoom: %.1f ",
                                       mouseLoc.x, mouseLoc.y,
                                       selsize.width, selsize.height,
                                       self.scrolledCanvas.magnification
                                       ]];
    
}

-(void) mouseDown:(NSEvent *)theEvent {
    downPos = [self convert:[theEvent locationInWindow]];
   // map->getBlockInfo(downPos.x, downPos.y);

    [self mouseMoved: theEvent];
}

-(void) mouseUp:(NSEvent *)theEvent {
    upPos = [self convert:[theEvent locationInWindow]];
    [self mouseMoved: theEvent];
}


@end
