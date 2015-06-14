#!/usr/bin/env node

var divbwt = require('../index.js').divbwt;

var t = new Buffer(Math.pow(2, 28) - 1);
t.fill('$');
var u = new Buffer(t.length);
var aux = new Buffer(4 * t.length);
divbwt(t, u, aux);
console.log('done');

