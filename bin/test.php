<?php

require __DIR__. '/../vendor/autoload.php';

use Mrsuh\PhpAst\Parser;
use Mrsuh\PhpAst\Printer;

$code = <<<'CODE'
<?php

namespace App;

class Test
{
    public function test($foo)
    {
        var_dump($foo);
    }
}
CODE;

$node = Parser::parse($code);
Printer::print($node);
