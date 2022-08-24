# PHP AST

:warning: WIP

### Requirements
* PHP >= 8.0 (with FFI)
* Linux(x86_64) / Darwin(x86_64)

## Usage

```bash
composer require mrsuh/php-ast
```

```php
<?php

require __DIR__. '/vendor/autoload.php';

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
```

```bash
[001] ZEND_AST_STMT_LIST
[003]   ZEND_AST_NAMESPACE
[003]     ZEND_AST_ZVAL "App"
[005]   ZEND_AST_CLASS "Test"
[006]     ZEND_AST_STMT_LIST
[007]       ZEND_AST_METHOD "test"
[007]         ZEND_AST_PARAM_LIST
[007]           ZEND_AST_PARAM
[007]             ZEND_AST_ZVAL "foo"
[008]         ZEND_AST_STMT_LIST
[009]           ZEND_AST_CALL
[009]             ZEND_AST_ZVAL "var_dump"
[009]             ZEND_AST_ARG_LIST
[009]               ZEND_AST_VAR
[009]                 ZEND_AST_ZVAL "foo"
```

## For contributors

### How to compile

```bash
git clone --recurse-submodules git@github.com:mrsuh/php-ast.git && cd php-ast
make php-src
make
```

### Debug

```bash
make debug
gdb php
run bin/test.php
```

### Docker

```bash
docker build -t php-ast .
docker run --rm -v $PWD:/code -it php-ast bash
make
php bin/test.php
```
