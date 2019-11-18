use 5.012;
use lib 't/lib';
use MyTest;
use Test::More;
use Test::Catch;
use Protocol::HTTP::Request;

subtest 'basic' => sub {
    my $req = Protocol::HTTP::Request->new({
        method       => METHOD_GET,
        uri          => "http://crazypanda.ru/hello/world",
        http_version => 10,
        headers      => {MyHeader => "my value"},
        body         => "my body",
    });
    
    is $req->to_string,
        "GET /hello/world HTTP/1.0\r\n".
        "MyHeader: my value\r\n".
        "Content-Length: 7\r\n".
        "Host: crazypanda.ru\r\n".
        "\r\n".
        "my body"
    ;
};

subtest 'no netloc in uri' => sub {
    my $req = Protocol::HTTP::Request->new({
        uri => "/hello",
    });
    
    is $req->to_string,
        "GET /hello HTTP/1.1\r\n".
        "Content-Length: 0\r\n".
        "\r\n"
    ;
};

subtest 'no uri' => sub {
    my $req = Protocol::HTTP::Request->new({});
    
    is $req->to_string,
        "GET / HTTP/1.1\r\n".
        "Content-Length: 0\r\n".
        "\r\n"
    ;
};

done_testing();