# divsufsort
node binding for Yuta Mori's libdivsufsort

> This library provides a simple and an efficient C API to construct a suffix array and a Burrows-Wheeler 
> transformed string from a given string over a constant-size alphabet. The algorithm runs in O(n log n) 
> worst-case time using only 5n+O(1) bytes of memory space, where n is the length of the string.

See: https://github.com/y-256/libdivsufsort

## Usage

```js
var divsufsort = require('divsufsort').divsufsort,
    divbwt = require('divsufsort').divbwt;

var lodash = require('lodash'),
    assert = require('assert');

/*
  Suffix array construction
 */
var t = new Buffer('abracadabra'), 
    sa = new Buffer(4 * t.length);  // Must be >= 4x input length

// "sa" receives the suffix array, packed as 32-bit integers. The function
// will throw an Error if anything goes wrong.
divsufsort(t, /* out */ sa);
assert.deepEqual(bufToUint32Array(sa), [10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2]);

/*
  Burroughs-Wheeler transform
 */
// TBD.


/* For testing */
function bufToUint32Array(buf) {
    var offsets = _.range(0, buf.length, 4);
    return _.map(offsets, function (idx) {
        return buf.readUInt32LE(idx);
    });
}

```

## Install

Ensure the libdivsufsort library and headers are installed as per 
instructions below. This addon uses whatever is installed on your 
system, not a vendored copy.

```bash
npm install divsufsort
```

### libdivsufsort for OSX

```bash
brew install homebrew/science/libdivsufsort
```

### libdivsufsort for Linux / Unix

* Requires cmake >= 2.4.2, make, C compiler.

```
git clone https://github.com/y-256/libdivsufsort
mkdir libdivsufsort/build
cd libdivsufsort/build
cmake -DCMAKE_BUILD_TYPE="Release" -DCMAKE_INSTALL_PREFIX="/usr/local" .. 
make && sudo make install
```
## Notes

The largest buffer I could allocate on 64-bit OSX builds of node:

var b = new Buffer(Math.pow(2, 30) - 1);  // Works
var c = new Buffer(Math.pow(2, 30));      // Fails

* 0.10.36 - RangeError: length > kMaxLength
* 0.12.0 - RangeError: Attempt to allocate Buffer larger than maximum size: 
  0x3fffffff bytes

So a bit less than 1GB in both cases. This means that the largest 
strings you can work with will be 256MB or so.

SA construction or BWT on a 256MB string blocks for about 2 secs on my laptop, 
so if you're not writing a console program you probably want to do it in an 
external process.

