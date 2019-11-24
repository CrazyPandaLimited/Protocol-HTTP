use 5.012;
use lib 't/lib';
use MyTest;
use Test::More;
use Test::Catch;
use Protocol::HTTP::Request;
use Protocol::HTTP::Message;

catch_run('[parse-response]');

subtest "basic" => sub {
    my $p = Protocol::HTTP::ResponseParser->new;
    $p->set_context_request(new Protocol::HTTP::Request({method => METHOD_GET}));
    my $raw =
        "HTTP/1.0 200 OK\r\n".
        "Host: host1\r\n".
        "\r\n";

    my ($res, $pos) = $p->parse($raw);

    ok $res->state != STATE_DONE;
    is $res->http_version, 10;
    is $res->code, 200;
    is $res->message, "OK";
    is $res->header("Host"), "host1";
    is $pos, length($raw);

    $res = $p->eof;
    is $res->state, STATE_DONE;
};

subtest 'error' => sub {
    my $p = Protocol::HTTP::ResponseParser->new;
    $p->set_context_request(new Protocol::HTTP::Request({method => METHOD_GET}));

    my ($res, $pos) = $p->parse("EPTA");
    is $res->state, STATE_ERROR;
    ok $res->error;
};

subtest 'reset' => sub {
    my $p = Protocol::HTTP::ResponseParser->new;
    $p->set_context_request(new Protocol::HTTP::Request({method => METHOD_GET}));
    $p->parse("HT");
    
    $p->reset;
    $p->set_context_request(new Protocol::HTTP::Request({method => METHOD_GET}));
    
    my ($res) = $p->parse("HTTP/1.0 200 OK\r\nContent-Length: 0\r\n\r\n");
    is $res->state, STATE_DONE;
    is $res->code, 200;
};

subtest 'backref' => sub {
    my $p = Protocol::HTTP::ResponseParser->new;
    $p->set_context_request(new Protocol::HTTP::Request({method => METHOD_GET}));
    
    my ($res)  = $p->parse("HTTP/1.0 200 OK\r\n");
    my ($res2) = $p->parse("Content-Length: 0\r\n\r\n");
    is $res2->state, STATE_DONE;
    is $res, $res2;
};

done_testing();