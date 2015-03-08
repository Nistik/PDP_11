//
//  PDPWindowController.m
//  PDP_11
//
//  Created by Nist on 05/03/15.
//  Copyright (c) 2015 Nist. All rights reserved.
//

#import "PDPWindowController.h"
#import "PDPEmulator.h"

@implementation PDPWindowController {
	PDPEmulator *_emulator;
}

- (instancetype)initWithWindow:(NSWindow *)window {
	self = [super initWithWindow:window];
	if (self) {
		PDPEmulator *myEmulator = new PDPEmulator();
		_emulator = myEmulator;
	}

	return self;
}


- (IBAction)fillROM:(id)sender {
	vector<Command> ccpCommands;

	NSArray *strings = [_inputField.string componentsSeparatedByString:@"\n"];
	for (NSString *string in strings) {
		NSArray *commandAndArgs = [string componentsSeparatedByCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@" "]];
		switch (commandAndArgs.count) {
			case 1:
				ccpCommands.push_back(Command([commandAndArgs[0] UTF8String]));
				break;
			case 2:
				ccpCommands.push_back(Command([commandAndArgs[0] UTF8String], [commandAndArgs[1] UTF8String]));
				break;
			case 3:
				ccpCommands.push_back(Command([commandAndArgs[0] UTF8String], [commandAndArgs[1] UTF8String], [commandAndArgs[2] UTF8String]));
				break;
			default:
				@throw [NSException new];
		}
	}

	_emulator->fillROMWithCommands(ccpCommands);
}

- (IBAction)stepButton:(id)sender {
	_emulator->tick();
	NSMutableString *output = _outputField.textStorage.mutableString;
	[output setString:@""];
	for (int i=0; i<8; ++i)
	{
		[output appendFormat:@"R%@: %@\n", @(i), @(_emulator->_registers[i])];
	}
}

- (void)dealloc {
	delete(_emulator);
}

@end
