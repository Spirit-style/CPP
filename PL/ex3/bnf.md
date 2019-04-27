<表达式> ::= <项><项后> | -<项><项后> | +<项><项后>
<项后> ::= <加法运算符><项><项后>|の
<项> ::= <因子><因后>
<因后>::=<乘法运算符><因子><因后>|の
<因子>::= <标识符>|<无符号整数>| ‘(’ <表达式>‘)’
<加法运算符> ::= +|-
<乘法运算符> ::= *|/
```cpp
enum symbol
{
    //终结符
    nul,
    beginsym,
    callsym,
    constsym,
    dosym,
    endsym,
    ifsym,
    oddsym,
    procsym,
    readsym,
    thensym,
    varsym,
    whilesym,
    writesym,
    ident,  //标识符
    number, //数字
    pluss,   //+ - * /
    minuss,
    times,
    slash,
    eql,       //=
    neq,       //#
    lss,       //<
    leq,       //<=
    gtr,       //>
    geq,       //>=
    lparen,    //(
    rparen,    //)
    comma,     //,
    semicolon, //;
    period,    //.
    becomes,   //:=
    //非终结符
    express
    termsuff
    term
    factsuff
};
```
