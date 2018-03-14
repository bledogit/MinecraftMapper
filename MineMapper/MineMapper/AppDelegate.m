//
//  AppDelegate.m
//  MineMapper
//
//  Created by Jose on 6/10/15.
//  Copyright (c) 2015 Jose. All rights reserved.
//

#import "AppDelegate.h"
#import "ViewController.h"

@interface AppDelegate ()

@end


@implementation AppDelegate


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
        NSLog(@"Did Finish Launching");
    
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
    NSLog(@"Application will terminate");

}

- (IBAction)newDocument:(id)sender {

}

- (IBAction)openDocument:(id)sender {
    NSOpenPanel* panel = [NSOpenPanel openPanel];
    [panel setCanChooseDirectories:YES];
    [panel setCanChooseFiles:NO];
    
    // This method displays the panel and returns immediately.
    // The completion handler is called when the user selects an
    // item or cancels the panel.
    [panel beginWithCompletionHandler:^(NSInteger result) {
        if (result == NSFileHandlingPanelOKButton) {
            NSURL*  theDoc = [[panel URLs] objectAtIndex:0];
            
            [panel close];
            
            NSLog(@"Document URL=%@", theDoc );
            NSWindow *current = [NSApplication sharedApplication].keyWindow;
            ViewController *controller = (ViewController*)current.contentViewController;
            
            controller.path = theDoc.path;
            controller.title = theDoc.path;
        }
        
    }];
}


- (IBAction)viewMapShow:(id)sender {
    NSLog(@"Map Show");
    NSWindow *current = [NSApplication sharedApplication].keyWindow;
    ViewController *controller = (ViewController*)current.contentViewController;
    [controller performLoadMap:  0];
}

- (IBAction)viewTopoMapShow:(id)sender {
    NSLog(@"Map Topo Show");
    NSWindow *current = [NSApplication sharedApplication].keyWindow;
    ViewController *controller = (ViewController*)current.contentViewController;
    [controller performLoadMap: 1];
}

- (IBAction)viewTestMapShow:(id)sender {
    NSLog(@"Map Show");
    NSWindow *current = [NSApplication sharedApplication].keyWindow;
    ViewController *controller = (ViewController*)current.contentViewController;
    [controller performTestMap];
}

- (IBAction)zoomIn:(id)sender {
    NSLog(@"Map Zoom in");
    NSWindow *current = [NSApplication sharedApplication].keyWindow;
    ViewController *controller = (ViewController*)current.contentViewController;
    [controller zoomIn];
}
- (IBAction)zoomOut:(id)sender {
    NSLog(@"Map Zoom out");
    NSWindow *current = [NSApplication sharedApplication].keyWindow;
    ViewController *controller = (ViewController*)current.contentViewController;
    [controller zoomOut];
}


@end
