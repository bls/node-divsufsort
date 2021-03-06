var expect = require('chai').expect;
var _ = require('lodash');

var divsufsort = require('../index.js').divsufsort,
    divbwt = require('../index.js').divbwt;

function bufToUint32Array(buf) {
    var offsets = _.range(0, buf.length, 4);
    return _.map(offsets, function (idx) {
        return buf.readUInt32LE(idx);
    });
}

describe('native', function() {
    describe('module', function () {
        it('should export the right functions', function () {
            expect(divsufsort).to.be.a('function');
            expect(divbwt).to.be.a('function');
        });
    });
    describe('divsufsort', function () {
        it('should accept exactly 2 arguments', function () {
            var a = new Buffer(0),
                b = new Buffer(0),
                c = new Buffer(0);

            expect(function () {
                divsufsort();
            }).to.throw(TypeError);

            expect(function () {
                divsufsort(a);
            }).to.throw(TypeError);

            expect(function () {
                divsufsort(a, b);
            }).to.not.throw(TypeError);

            expect(function () {
                divsufsort(a, b, c);
            }).to.throw(TypeError);
        });
        it('should not accept non-buffer argument types', function () {
            var testArgs = [null, undefined, -1, 'test', NaN, {}];
            _.forEach(testArgs, function (arg1) {
                _.forEach(testArgs, function (arg2) {
                    expect(function () {
                        divsufsort(arg1, arg2);
                    }).to.throw(TypeError);
                });
            });
        });
        /*
         it('should reject the same buffer as both input and output', function() {
         var a = new Buffer(0);
         expect(function () {
         divsufsort.divsufsort(a, a);
         }).to.throw(Error);
         });
         */
        it('should check buffer sizes', function () {
            var a = new Buffer('abba'),
                b = new Buffer(15),  // size < 4 * n
                c = new Buffer(16);  // size == 4 * n
            expect(function () {
                divsufsort(a, b);
            }).to.throw(Error);
            expect(function () {
                divsufsort(a, c);
            }).to.not.throw(Error);
        });
        it('should handle the trivial case', function () {
            var a = new Buffer('a');
            var b = new Buffer('zzzz'); // Junk
            expect(b.readUInt32LE(0)).to.not.be.equal(0);
            divsufsort(a, b);
            expect(b.readUInt32LE(0)).to.be.equal(0);
        });
        it('should handle a simple case', function () {
            var t = new Buffer('abracadabra'),
                sa = new Buffer(4 * t.length);
            var ret = divsufsort(t, sa);
            expect(ret).to.be.equal(0);
            expect(bufToUint32Array(sa)).to.be.eql([
                10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2
            ]);
        });
    });

    describe('divbwt', function () {
        it('should accept exactly 3 arguments', function () {
            var a = new Buffer(0),
                b = new Buffer(0),
                c = new Buffer(0);

            expect(function () {
                divsufsort();
            }).to.throw(TypeError);

            expect(function () {
                divsufsort(a);
            }).to.throw(TypeError);

            expect(function () {
                divsufsort(a, b);
            }).to.not.throw(TypeError);

            expect(function () {
                divsufsort(a, b, c);
            }).to.throw(TypeError);
        });
        it('should not accept non-buffer argument types', function () {
            var testArgs = [null, undefined, -1, 'test', NaN, {}];
            _.forEach(testArgs, function (arg1) {
                _.forEach(testArgs, function (arg2) {
                    _.forEach(testArgs, function(arg3) {
                        expect(function () {
                            divbwt(arg1, arg2, arg3);
                        }).to.throw(TypeError);
                    });
                });
            });
        });
        // TODO: Buffer size checks
        it('should handle a simple case', function() {
            var t = new Buffer('banana'),
                u = new Buffer(t.length),
                aux = new Buffer(4 * t.length);
            var ret = divbwt(t, u, aux);
            var us = u.toString(),
                result = us.slice(0, ret) + '$' + us.slice(ret);
            expect(result).to.be.equal('annb$aa');
        });
    });
});
