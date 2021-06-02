#include <iostream>
#include <fstream>
#include <bitset>

#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"
#include "BitsWriter.h"
#include "BitsReader.h"
#include "Treap.h"
#include "MTFTransform.h"
#include "BWTTransform.h"
#include "Timer.h"
#include "RLE.h"
#include "ArithmeticCoding.h"
#include "LongDecimal.h"

using namespace std;


void testHuffman() {
    Timer t;
    HuffmanEncoder he("testfiles/data.txt");
    he.encode();
    he.writeToBinary("testfiles/compressed.huff");
    cout << "Huffman encode - " << t.elapsed() << "s" << endl;

    t.reset();
    HuffmanDecoder hd("testfiles/compressed.huff");
    hd.decodeTo("testfiles/outh.txt");
    cout << "Huffman decode - " << t.elapsed() << "s" << endl;
}

void mtfTimeCompare() {
    Timer t;
    mtf("testfiles/data.txt", "testfiles/out1.mtf.txt");
    cout << "MTF using treap - " << t.elapsed() << "s" << endl;

    t.reset();
    mtfSlower("testfiles/data.txt", "testfiles/out2.mtf.txt");
    cout << "MTF using list - " << t.elapsed() << "s" << endl;
}

void testBwt() {
    Timer t;
    bwt("testfiles/data.txt", "testfiles/out.bwt.txt");
    cout << "BWT - " << t.elapsed() << "s" << endl;

    t.reset();
    bwtDecode("testfiles/out.bwt.txt", "testfiles/out.txt");
    cout << "BWTDecode - " << t.elapsed() << "s" << endl;
}

void B2ZipCompress(string finname, string foutname) {
    int shift = 0;

    Timer t;
    shift += bwt(finname, finname + ".bwt", shift);
    cout << "BWT - " << t.elapsed() << "s" << endl;

    t.reset();
    shift += mtf(finname + ".bwt", finname + ".mtf", shift);
    cout << "MTF - " << t.elapsed() << "s" << endl;

    t.reset();
    HuffmanEncoder he(finname + ".mtf", shift);
    he.encode();
    he.writeToBinary(foutname);
    cout << "Huffman - " << t.elapsed() << "s" << endl;
}

void B2ZipDecompress(string finname, string foutname) {
    int counter = sizeof(unsigned);
    ifstream fin(finname);
    char c;
    for (int i = 0; i < counter; i++, fin.get(c)) {}
    while (fin.get(c)) {
        counter++;
        if (c == '\0') break;
    }
    fin.close();
    
    HuffmanDecoder hd(finname, counter);
    hd.decodeTo(finname + ".uhuff");
    mtfDecode(finname + ".uhuff", finname + ".umtf", sizeof(int));
    bwtDecode(finname + ".umtf", foutname);
}

void testRLE() {
    Timer t;
    rle("testfiles/data.txt", "testfiles/out.rle.txt");
    cout << "RLE - " << t.elapsed() << "s" << endl;

    t.reset();
    rleDecode("testfiles/out.rle.txt", "testfiles/out.txt");
    cout << "RLEDecode - " << t.elapsed() << "s" << endl;
}

void testArithmeticCoding() {
    Timer t;
    arithmeticEncode("testfiles/data.txt", "testfiles/out.arc.txt");
    cout << "Arithmetic coding - " << t.elapsed() << "s" << endl;

    t.reset();
    arithmeticDecode("testfiles/out.arc.txt", "testfiles/out.txt");
    cout << "Arithmetic decode - " << t.elapsed() << "s" << endl;
}

int main()
{
    //mtfTimeCompare();

    //Timer t;
    //testHuffman();
    //cout << "Only Huffman - " << t.elapsed() << "s" << endl << endl;

    //t.reset();
    //B2ZipCompress("testfiles/data.txt", "testfiles/compressed.dat");
    //cout << "Compress - " << t.elapsed() << "s" << endl << endl;

    //t.reset();
    //B2ZipDecompress("testfiles/compressed.dat", "testfiles/out.txt");
    //cout << "Decompress - " << t.elapsed() << "s" << endl;

    testArithmeticCoding();

    //testBwt();

    //LongDecimal ld1(.3642);

    //for (auto byte : ld1.getBytes()) {
    //    cout << bitset<8>(byte);
    //}
    //cout << endl;

    //cout << ld1.toDouble();

    return 0;
}
