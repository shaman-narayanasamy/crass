# this lists the binaries to produce, the (non-PHONY, binary) targets in
bin_PROGRAMS = crass
if ASSEMBLY_WRAPPER
bin_PROGRAMS += crass-assembler
endif

AM_CXXFLAGS = @XERCES_CPPFLAGS@ @LIBCRISPR_CPPFLAGS@ -Werror -pedantic -Wall
AM_LDFLAGS = @XERCES_LDFLAGS@ @LIBCRISPR_LDFLAGS@ @LIBCRISPR_LIBS@ @zlib_flags@



crass_SOURCES =\
PatternMatcher.cpp PatternMatcher.h\
Rainbow.cpp Rainbow.h\
crass.cpp crass.h\
WuManber.cpp WuManber.h\
LoggerSimp.cpp LoggerSimp.h\
SeqUtils.cpp SeqUtils.h\
CrisprNode.cpp CrisprNode.h\
NodeManager.cpp NodeManager.h\
libcrispr.cpp libcrispr.h\
WorkHorse.cpp WorkHorse.h\
SpacerInstance.cpp SpacerInstance.h\
ReadHolder.cpp ReadHolder.h\
SmithWaterman.cpp SmithWaterman.h\
StringCheck.cpp StringCheck.h\
kseq.cpp kseq.h\
GraphDrawingDefines.h\
crassDefines.h\
StatsManager.h\
SearchChecker.cpp SearchChecker.h\
ksw.c ksw.h\
Types.h\
Aligner.cpp Aligner.h


crass_assembler_SOURCES =\
AssemblyWrapper.cpp AssemblyWrapper.h\
config.h\
crassDefines.h\
kseq.cpp kseq.h\
SeqUtils.cpp SeqUtils.h

