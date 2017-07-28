# Campus As a Lab Calibiration cal2ibrate

This is the code for the cal2ibrate project supported by the Princeton Campus as a lab award. This code polls all ADCs as well as the Si7021 temperature/humidity sensor, and then pushes to a mongo database.

## Instructions

1. Using the build.particle.io interface load the photon code onto your paticle. 
2. Setup a mongo database somewhere. Docker is a great wait to do this.
3. Run the SSE code, filling in the Particle Token and Mongo IP

## Parts List

- Particle Photon (https://www.adafruit.com/product/2721)
- Si 7021 (https://www.adafruit.com/product/3251)
- Patch Wire (https://www.adafruit.com/product/1956)
- Tiny Breadboard (https://www.adafruit.com/product/65)

## Big Ups
Adafruit (https://www.adafruit.com) is a wonderful store with wonderful products and excellent (and free) code examples all provided under the BSD License.
