PROGRAM DPiSSL(input,output);
{
一个SSL维护区间SEGi的例子
以线段染色为例
}
CONST
	maxlev=16;
    inf=9999999;
    maxn=5000000;
    none=-1;
    maxp=1000;
VAR
    val,down,next,pre:array[0..maxn]of longint;
    segi:array[0..maxn]of longint;        //segi信息 以染的颜色为例 初始时整个平面为空(0)
    Last:array[0..maxlev]of longint;        //last存储搜索过程中在每一层链表里最后访问的节点
    Path:array[1..maxp]of longint;          //path存储搜索路径
    bt:array[1..maxn]of boolean;            //该节点是否为某块的顶部节点 用于判断横向的实边
    SLSize,PathSize:longint;
    op,l,r,c,right:longint;
    Function RandomLev:longint;             //随机得出高度
    Var
        h:longint;
    Begin
        h:=1;
        while((random(4)=0)and(h<maxlev))do inc(h);
        RandomLev:=h;
    End;
    Procedure init;                         //初始化跳表
    Var
    	i:longint;
    Begin
        fillchar(bt,sizeof(bt),false);
        fillchar(segi,sizeof(segi),0);
    	val[maxn]:=inf;
        for i:=0 to maxlev do
        begin
        	val[i]:=-inf;
            down[i]:=i-1;
            next[i]:=maxn;
            pre[i]:=none;
        end;
        down[0]:=none;
        SLSize:=maxlev;
    End;
    Function search(v:longint):longint;     //搜索v
    Var
    	p,lv,color:longint;
    Begin
        p:=maxlev;
        lv:=maxlev;
        PathSize:=0;
        while(p<>none)do
        begin
        	inc(PathSize);
            Path[PathSize]:=p;
            if(val[next[p]]<=v)then
            begin
                p:=next[p];
            end else begin
            	last[lv]:=p;
                lv:=lv-1;
                p:=down[p];
            end;
        end;
        search:=Path[PathSize];
    End;
    Function ask(v:longint):longint;
    Var
    	p:longint;
    Begin
    	p:=maxlev;
        while p<>none do
        begin
            if segi[p]<>0 then exit(segi[p]);
            if val[next[p]]<=v then
            	p:=next[p]
            else
            	p:=down[p];
        end;
        exit(0);
    End;
    Procedure update;
    Var
        i,p:longint;
    Begin
    	for i:=1 to PathSize-1 do
        begin
            p:=Path[i];
            if segi[p]<>0 then
            begin
                segi[down[p]]:=segi[p];
                if bt[next[p]] then
                    segi[next[p]]:=segi[p];
                segi[p]:=0;
            end;
        end;
    End;
    Procedure insert(v:longint);            //插入
    Var
    	h,i,p,tmp:longint;
    Begin
        h:=RandomLev;
        tmp:=none;
        if val[search(v)]=v then
        begin
            update;         //沿path(v)下分区间信息
    	end else begin
            update;         //沿path(v)下分区间信息
            segi[SLSize+1]:=segi[Path[PathSize]];
            for i:= 0 to h do
            begin
                p:=last[i];
                inc(SLSize);
                val[SLSize]:=v;
                down[SLSize]:=tmp; tmp:=SLSize;
                next[SLSize]:=next[p];
                pre[SLSize]:=p;
                next[p]:=SLSize;
                pre[next[SLSize]]:=SLSize;
            end;
            bt[SLSize]:=true;
        end;
        bt[SLSize]:=true;
    End;
    Procedure paint(p,l,r,c:longint);       //将p对应的区间与[l,r)区间的交染成c颜色
    Begin
        if (p=none)or(val[p]>=r)or (right<=l) then exit;
        if (val[p]>=l)and(right<=r) then
        begin
            segi[p]:=c;
            exit;
        end;
        if bt[next[p]] then paint(next[p],l,r,c);
        right:=val[next[p]];
        paint(down[p],l,r,c);
    End;
    Procedure delete(v:longint);            //删除
    Var
    	i,p,c1,c2:longint;
    Begin
    //我在这里写的删除并不是完全按照论文中所写的进行 而是使用了另一种写法 这里可以显示出跳表的灵活性
    	if val[search(v)]<>v then
        begin
            writeln('ERROR!');
        	exit;
        end;
        p:=Path[PathSize];
        c1:=ask(val[pre[p]]);
        c2:=ask(val[p]);
        if c1<>c2 then  //v是某个染色区间的端点
        begin
            writeln('ERROR!');
            exit;
        end;
        paint(maxlev,val[pre[p]],val[next[p]],c1);
        for i:=0 to maxlev do
        begin
            if val[last[i]]<>v then break;
            p:=pre[last[i]];
            next[p]:=next[next[p]];
            pre[next[p]]:=p;
        end;
        writeln('Done');
    End;
BEGIN
	randomize;
    init;
    while not eof do
    begin
        read(op);
        if op=1 then        //第一种操作 染色
        begin
            read(l,r,c);    //将[l,r)染成c颜色
            insert(l);
            insert(r);
            right:=inf;
            paint(maxlev,l,r,c);   //将[l,r)染成c颜色
            writeln('Done');
        end;
        if op=2 then        //第二种操作 询问
        begin
            read(l);
            writeln('Color(',l,')=',ask(l));
                            //询问x=l处的颜色
        end;
        if op=3 then        //第三种操作 删除
        begin
            read(l);
            delete(l);      //第三种操作 删除
        end;
    end;
    writeln(SLSize);
END.
