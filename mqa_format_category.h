/*
This file is part of Kappa.
Copyright (C) 2014-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
*/

#ifndef MQA_FORMAT_CATEGORY_H
#define MQA_FORMAT_CATEGORY_H

/*
The AMQP Format Code Category enumeration.
*/
enum format_category {
    /*
    The size of fixed-width data is determined based solely on the subcategory
    of the format code for the fixed width value.
    */
    fixed,

    /*
    The size of variable-width data is determined based on an encoded size that
    prefixes the data. The width of the encoded size is determined by the
    subcategory of the format code for the variable width value.
    */
    variable,

    /*
    Compound data is encoded as a size and a count followed by a polymorphic
    sequence of count constituent values. Each constituent value is preceded by
    a constructor that indicates the semantics and encoding of the data that
    follows. The width of the size and count is determined by the subcategory
    of the format code for the compound value.
    */
    compound,

    /*
    Array data is encoded as a size and count followed by an array element
    constructor followed by a monomorphic sequence of values encoded according
    to the supplied array element constructor. The width of the size and count
    is determined by the subcategory of the format code for the array.
    */
    array
};

/*
Reads a format code category from a stream.
@stream:
*/
enum format_category format_code_read(FILE* stream);

/*
Writes a format code category into the supplied output stream.
@stream: a binary output stream.
@format_category:
*/
void format_category_write(FILE* stream, enum format_category format_category);

#endif

