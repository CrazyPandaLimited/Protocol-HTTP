use 5.012;
use lib 't/lib';
use MyTest;
use Test::More;
use Test::Catch;
use Protocol::HTTP::Response;

catch_run('[compile-cookies]');

subtest 'request cookies' => sub {
    subtest '"cookies" in ctor' => sub {
        my $req = new Protocol::HTTP::Request({
            cookies => {a => 1},
        });
        is $req->to_string,
            "GET / HTTP/1.1\r\n".
            "Cookie: a=1\r\n".
            "\r\n";
    };
    subtest 'cookies()' => sub {
        my $req = new Protocol::HTTP::Request;
        $req->cookies({junk => 1}); # should be overwritten
        my $hash = {a => 1};
        $req->cookies($hash);
        is $req->to_string,
            "GET / HTTP/1.1\r\n".
            "Cookie: a=1\r\n".
            "\r\n";
        is_deeply $req->cookies, $hash;
    };
    subtest 'cookie()' => sub {
        my $req = new Protocol::HTTP::Request;
        is $req->cookie("session"), undef;
        $req->cookie("session", "abc");
        is $req->cookie("session"), "abc";
        is $req->to_string,
            "GET / HTTP/1.1\r\n".
            "Cookie: session=abc\r\n".
            "\r\n";
    };
};

subtest 'response cookies' => sub {
    subtest '"cookies" in ctor' => sub {
        my $res = new Protocol::HTTP::Response({
            cookies => {session => {
                value     => "123",
                domain    => "epta.ru",
                path      => "/",
                max_age   => 1000,
                secure    => 1,
                http_only => 1,
                same_site => COOKIE_SAMESITE_LAX,
            }},
        });
        is $res->to_string,
            "HTTP/1.1 200 OK\r\n".
            "Connection: keep-alive\r\n".
            "Content-Length: 0\r\n".
            "Set-Cookie: session=123; Domain=epta.ru; Path=/; Max-Age=1000; Secure; HttpOnly; SameSite=Lax\r\n".
            "\r\n";
    };
    subtest 'cookies()' => sub {
        my $req = new Protocol::HTTP::Request;
        $req->cookies({junk => 1}); # should be overwritten
        my $hash = {a => 1};
        $req->cookies($hash);
        is $req->to_string,
            "GET / HTTP/1.1\r\n".
            "Cookie: a=1\r\n".
            "\r\n";
        is_deeply $req->cookies, $hash;
    };
    subtest 'cookie()' => sub {
        my $req = new Protocol::HTTP::Request;
        is $req->cookie("session"), undef;
        $req->cookie("session", "abc");
        is $req->cookie("session"), "abc";
        is $req->to_string,
            "GET / HTTP/1.1\r\n".
            "Cookie: session=abc\r\n".
            "\r\n";
    };
};

done_testing();
