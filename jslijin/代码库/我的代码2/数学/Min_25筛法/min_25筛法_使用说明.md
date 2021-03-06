### min_25筛法_使用说明



**【任务】**

解决一类积性函数$F(x)$求和的问题



**【适用条件】**

1.被求和函数$F(x)$是积性函数

2.$F(1)$已知，一般为可口算的常数

3.$F(p)$一般是关于p的一个简单的低次多项式，比如$F(p)=4 * p^2+3 * p+2$

$F(p)$可以写成$a * f_1(p)+b * f_2(p)+c * f_3(p)..$

其中每个$f_i(x)$都是积性函数，一般是x的幂次

4.$F(p[i]^e)$很容易求出，在模板里是函数$f(i,e)$



**【基本原理】**

是一种埃氏筛法的扩展，其定义的函数可以看成是这个筛法执行完若干次之后，

没有被筛去的所有数的函数$F(x)$之和

定义与公式：
$$
\Large g(x,j)=\sum_{i=2}^xi^k[i是质数，或者i的最小质因子>p_j]
$$

$$
\Large S(x,j)=\sum_{i=2}^xF(i)[i的最小质因子\ge p_j]
$$

$$
\Large g(x,j)=g(x,j-1)-f(p_j)(g(\lfloor\frac{x}{p_j}\rfloor,j-1)-g(p_j-1,j-1))
$$

$$
\Large S(x,j)=\sum_{i=j}^m\sum_{e\ge 1,p_i^{e+1}\le x}S(\lfloor \frac{x}{p_i^e}\rfloor,i+1)*F(p_i^e)+F(p_i^{e+1})
$$

上述第三个公式是基于对质数和合数的讨论的，g函数增加的部分含义是：恰好以$p_j$作为最小质因子的合数的函数之和，那么当提取了一个$p_j$之后，剩下的部分范围很容易得到，同样也是以不低于$p_j$作为最小质因子的，可以是合数，也可以是不小于$p_j$的质数，所以括号里要减去小于$p_j$的那些质数，也就是前$j-1$个质数的函数值；第四个公式，由于S定义的范围里面没有1，所以漏算了质数的任意幂次，我们加上质数的至少两次幂的函数值，最终还缺少所有质数本身的函数值之和，以及1处的函数值





**【注释处需要修改的地方说明】**

按照出现的顺序：

1.初始化里修改$f_1$

2.$f(i,e)$表示$F(p[i]^e)$,$p[i]$表示第$i$个质数

3.$s[i]$表示前i个质数的函数之和$f(1)+…+f(i)$

4.$h[k]$表示$2..x(k)$的$x^0$之和，也就是$f(x)$之和 ，$g[k]$表示同样区间$x^1$之和

5.转移处修改：

(h[i]-=(ll)1*(h[k]-(j-1)))%=_p;

(g[i]-=(ll)p[j]*(g[k]-s[j-1])%_p)%=_p；

设立的函数设为f[i]表示质数的k次方:

格式是：(f[i]-=(ll)p[j]^k^ * ( f[k] - s[j-1] ))

s[i]就是前i个质数的$f(x)$函数值之和

6.$F(k)$表示$2..x(k)$中质数处的积性函数$F(x)$之和，这是合并函数：

根据事先拆分的$g[]$和$h[]$来合并，默认是$F(p)=p-1$，$p$是质数

7.合并函数，与上面类似，$G(no)$表示前$no$个质数处的积性函数$F(x)$之和