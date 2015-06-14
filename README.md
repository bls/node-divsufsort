# divsufsort
node.js bindings for libdivsufsort

This is a thin wrapper around libdivsufsort by Yuta Mora. 

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
var t = new Buffer('abracadabra'); 
var sa = new Buffer(4 * t.length);  // Must be >= 4x input length

// "sa" receives the suffix array, packed as 32-bit integers.
divsufsort(t, sa);

assert.deepEqual(sa, [10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2]);

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
