/*
try {
  var divsufsort = require('./build/Release/divsufsort.node');
} catch (e) {
  var divsufsort = require('./build/Debug/divsufsort.node');
}
*/

var divsufsort = require('./build/Release/divsufsort.node');

module.exports = divsufsort;
