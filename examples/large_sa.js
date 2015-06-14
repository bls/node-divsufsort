#!/usr/bin/env node

var divsufsort = require('../index.js').divsufsort;

var t = new Buffer(Math.pow(2, 28) - 1);
t.fill('$');
var sa = new Buffer(4 * t.length);
divsufsort(t, sa);
console.log('done');

