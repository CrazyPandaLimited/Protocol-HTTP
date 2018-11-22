use strict;
use XS::Install;

my %params = (
    NAME          => 'Protocol::HTTP::XS',
    VERSION_FROM  => 'lib/Protocol/HTTP/XS.pm',
    ABSTRACT_FROM => 'lib/Protocol/HTTP/XS.pod',
    BIN_DEPS  => ['Panda::Lib', 'Panda::Export', 'UniEvent', 'XS::Framework', 'URI::XS'],
    DEFINE    => $ENV{DEBUG} ? '-DDEBUG' : '',
    SRC       => ['src'],
    INC       => '-Isrc',
    LIBS      => '',
    BIN_SHARE => {
        INCLUDE  => {
            'src'           => '/'
        },
    },
    CCFLAGS  => '-Wall -Wextra',
    test     => {
        SRC                  => 't',
        RECURSIVE_TEST_FILES => 1,
    },
    OPTIMIZE => '-O2 -g',
    #CC => 'clang++',
);

if ($ENV{TEST_FULL}) {
    $params{LIBS}[0] .= ' -lubsan';
    ($params{CCFLAGS}||='') .= ' -fsanitize=undefined';
}

write_makefile(%params);
