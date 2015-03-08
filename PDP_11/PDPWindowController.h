//
//  PDPWindowController.h
//  PDP_11
//
//  Created by Nist on 05/03/15.
//  Copyright (c) 2015 Nist. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface PDPWindowController : NSWindowController
@property(assign, nonatomic) IBOutlet NSTextView *inputField;
@property(assign, nonatomic) IBOutlet NSTextView *outputField;

- (IBAction)fillROM:(id)sender;
- (IBAction)stepButton:(id)sender;
@end
