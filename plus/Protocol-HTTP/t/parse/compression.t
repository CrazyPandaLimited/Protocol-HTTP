use 5.012;
use lib 't/lib';
use MyTest;
use Test::More;
use Test::Catch;
use Protocol::HTTP::Request;
use Protocol::HTTP::Message;

catch_run('[parse-compression]');

done_testing;
