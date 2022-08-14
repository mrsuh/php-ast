<?php

namespace Mrsuh\PhpAst;

class Parser
{
    private static ?\FFI $libc = null;

    private static function init(): void
    {
        if (self::$libc !== null) {
            return;
        }

        if (\version_compare(PHP_VERSION, '8.0.0', '<')) {
            throw new \RuntimeException('Unsupported PHP version');
        }

        if (\php_uname('m') !== 'x86_64') {
            throw new \RuntimeException('Unsupported machine type');
        }

        switch (\php_uname('s')) {
            case 'Linux':
                $libraryFileName = 'ast_linux.so';
                break;
            case 'Darwin':
                $libraryFileName = 'ast_darwin.dylib';
                break;
            default:
                throw new \RuntimeException('Unsupported operating system');
        }

        self::$libc = \FFI::cdef(
            file_get_contents(__DIR__ . '/../library/ast.h'),
            __DIR__ . "/../library/" . $libraryFileName);
    }

    public static function parse(string $content): Node
    {
        self::init();

        $libcAst = self::$libc->get_ast('content');

        return self::toNode($libcAst);
    }

    private static function toNode(\FFI\CData $libcAst): Node
    {
        $ast = $libcAst[0];

        $node         = new Node();
        $node->kind   = $ast->kind;
        $node->attr   = $ast->attr;
        $node->value  = $ast->value;
        $node->lineno = $ast->lineno;

        if ($ast->children > 0) {
            for ($i = 0; $i < $ast->children; $i++) {
                $node->children[] = self::toNode($ast->child[$i]);
            }
        }

        return $node;
    }
}
