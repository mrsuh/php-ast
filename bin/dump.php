<?php

require __DIR__. '/../vendor/autoload.php';

use Mrsuh\PhpAst\Parser;
use Mrsuh\PhpAst\Printer;

$filePath = $argv[1] ?? '';
if(!is_file($filePath)) {
    exit(1);
}

$content = file_get_contents($filePath);

$node = Parser::parse($content);
Printer::print($node);
