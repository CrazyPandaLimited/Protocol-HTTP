use 5.012;
use lib 't/lib';
use MyTest;
use Test::More;
use Test::Catch;
use Protocol::HTTP::Request;

catch_run('[compile-form]');

my $sample =
    "POST / HTTP/1.1\r\n".
    "Content-Length: 226\r\n".
    "Content-Type: multipart/form-data; boundary=-----------------------xn654lb75PltJaTBy\r\n".
    "\r\n".

    "-----------------------xn654lb75PltJaTBy\r\n".
    "Content-Disposition: form-data; name=\"k1\"\r\n".
    "\r\n".
    "v1\r\n".

    "-----------------------xn654lb75PltJaTBy\r\n".
    "Content-Disposition: form-data; name=\"k2\"\r\n".
    "\r\n".
    "v2\r\n".

    "-----------------------xn654lb75PltJaTBy--\r\n"
;

subtest "simple multipart/form-data" => sub {
    MyTest::native_srand(777);
    my $req = Protocol::HTTP::Request->new({
        form => [k1 => 'v1', k2 => 'v2'],
    });
    is $req->to_string, $sample;
};

subtest "multipart/form-data (2)" => sub {
    MyTest::native_srand(777);
    my $req = Protocol::HTTP::Request->new({
        form => {
            enc_type => ENCODING_MULTIPART,
            fields   => [k1 => 'v1', k2 => 'v2'],
        },
    });
    is $req->to_string, $sample;
};

subtest "multipart/form-data (3)" => sub {
    MyTest::native_srand(777);
    my $req = Protocol::HTTP::Request->new({
        uri  => '/?k1=v1&k2=v2',
        form => ENCODING_MULTIPART,
    });
    is $req->to_string, $sample;
};

subtest "application/x-www-form-urlencoded" => sub {
    my $req = Protocol::HTTP::Request->new({
        form => {
            enc_type => ENCODING_URL,
            fields   => [k1 => 'v1', k2 => 'v2'],
        },
    });
    is $req->to_string,
        "GET /?k1=v1&k2=v2 HTTP/1.1\r\n".
        "\r\n"
    ;
};

done_testing;
