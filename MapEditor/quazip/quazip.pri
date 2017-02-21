INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
HEADERS += \
        $$PWD/crypt.h \
        $$PWD/ioapi.h \
        $$PWD/JlCompress.h \
        $$PWD/quaadler32.h \
        $$PWD/quachecksum32.h \
        $$PWD/quacrc32.h \
        $$PWD/quagzipfile.h \
        $$PWD/quaziodevice.h \
        $$PWD/quazipdir.h \
        $$PWD/quazipfile.h \
        $$PWD/quazipfileinfo.h \
        $$PWD/quazip_global.h \
        $$PWD/quazip.h \
        $$PWD/quazipnewinfo.h \
        $$PWD/unzip.h \
        $$PWD/zip.h \
    $$PWD/zlib-1.2.11/crc32.h \
    $$PWD/zlib-1.2.11/deflate.h \
    $$PWD/zlib-1.2.11/gzguts.h \
    $$PWD/zlib-1.2.11/inffast.h \
    $$PWD/zlib-1.2.11/inffixed.h \
    $$PWD/zlib-1.2.11/inflate.h \
    $$PWD/zlib-1.2.11/inftrees.h \
    $$PWD/zlib-1.2.11/trees.h \
    $$PWD/zlib-1.2.11/zconf.h \
    $$PWD/zlib-1.2.11/zlib.h \
    $$PWD/zlib-1.2.11/zutil.h

SOURCES += $$PWD/qioapi.cpp \
           $$PWD/JlCompress.cpp \
           $$PWD/quaadler32.cpp \
           $$PWD/quacrc32.cpp \
           $$PWD/quagzipfile.cpp \
           $$PWD/quaziodevice.cpp \
           $$PWD/quazip.cpp \
           $$PWD/quazipdir.cpp \
           $$PWD/quazipfile.cpp \
           $$PWD/quazipfileinfo.cpp \
           $$PWD/quazipnewinfo.cpp \
           $$PWD/unzip.c \
           $$PWD/zip.c \
    $$PWD/zlib-1.2.11/adler32.c \
    $$PWD/zlib-1.2.11/compress.c \
    $$PWD/zlib-1.2.11/crc32.c \
    $$PWD/zlib-1.2.11/deflate.c \
    $$PWD/zlib-1.2.11/gzclose.c \
    $$PWD/zlib-1.2.11/gzlib.c \
    $$PWD/zlib-1.2.11/gzread.c \
    $$PWD/zlib-1.2.11/gzwrite.c \
    $$PWD/zlib-1.2.11/infback.c \
    $$PWD/zlib-1.2.11/inffast.c \
    $$PWD/zlib-1.2.11/inflate.c \
    $$PWD/zlib-1.2.11/inftrees.c \
    $$PWD/zlib-1.2.11/trees.c \
    $$PWD/zlib-1.2.11/uncompr.c \
    $$PWD/zlib-1.2.11/zutil.c
