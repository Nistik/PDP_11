//
//  PDPWindowController.m
//  PDP_11
//
//  Created by Nist on 05/03/15.
//  Copyright (c) 2015 Nist. All rights reserved.
//

#import "PDPWindowController.h"
#import "PDPEmulator.h"

@implementation PDPWindowController
{
	PDPEmulator      *_emulator;
	__strong NSTimer *_timer;
}

- (instancetype) initWithWindow:(NSWindow *)window
{
	self = [super initWithWindow:window];
	if (self)
	{
		PDPEmulator *myEmulator = new PDPEmulator();
		_emulator               = myEmulator;
	}

	return self;
}


- (IBAction) fillROM:(id)sender
{
	_emulator->fillROM();
}

- (IBAction) startButton:(id)sender
{
	[_timer invalidate];
	_timer = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(drawLine:) userInfo:nil repeats:YES];
}

- (IBAction) stopButton:(id)sender
{
	[_timer invalidate];
}


- (void) drawLine:(id)drawLine
{
	for (int i = 0; i < 1000; ++i)
	{
		_emulator->tick();
	}
	[self stepButton:nil];
}

- (IBAction) stepButton:(id)sender
{
	_emulator->tick();
	NSMutableString *output = _inputField.textStorage.mutableString;
	[output setString:@""];
	for (int i = 0; i < 8; ++i)
	{
		[output appendFormat:@"R%@: %@\n", @(i), @(_emulator->_registers[i])];
	}

	_vramView.image = [self vramImage];
}

- (NSImage *) vramImage
{
	CGSize     imageSize  = CGSizeMake(352, 352);
	const uint vramLength = 30976;

	NSBitmapImageRep *imageRep = [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:NULL pixelsWide:352 pixelsHigh:352 bitsPerSample:sizeof(float) samplesPerPixel:4 hasAlpha:1 isPlanar:0 colorSpaceName:NSCalibratedRGBColorSpace bytesPerRow:352 * 3 * sizeof(float) bitsPerPixel:4 * sizeof(float)];

	uint      imageContextDataCoursor = 0;
	for (uint v                       = 0; v < vramLength / 2; ++v)
	{
		uint16    vramTwoBytes = _emulator->_VRAM[v];
		for (uint b            = 0; b < 2; ++b)
		{
			uint8     *bytePointer = ((uint8 *) &vramTwoBytes) + b;
			for (uint p            = 0; p < 4; ++p)
			{
				uint8 c     = (uint8) ((*bytePointer & (0b11 << p * 2)) >> p * 2);
				float color = (((float) (0xff / 3)) * c) / 255.f;

				uint x = ((v * 2 + b) * 4 + p) % 352;
				uint y = ((v * 2 + b) * 4 + p) / 352;
				[imageRep setColor:[NSColor colorWithCalibratedRed:color green:color blue:color alpha:1] atX:x y:y];
//				NSLog(@"%u %u", x, y);
			}
		}
	}

	NSImage *image = [NSImage new];
	[image addRepresentation:imageRep];
	return image;
}

- (void) dealloc
{
	delete(_emulator);
}
@end
