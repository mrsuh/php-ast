<?php

namespace Mrsuh\PhpAst;

class Printer
{
    public static function print(Node $node, int $indent = 0): void
    {
        printf("[%03d] %s%s%s\n",
            $node->lineno,
            (str_repeat(' ', $indent)),
            $node->kind,
            $node->value ? sprintf(" \"%s\"", $node->value) : ''
        );
        foreach ($node->children as $child) {
            self::print($child, $indent + 2);
        }
    }
}
