PROGRAM DPiSSL(input,output);
{
一个SSL维护区间DPi的例子
以维护区间内点的个数为例
}
CONST
	maxlev=16;
    inf=9999999;
    maxn=5000000;
    none=-1;
    maxp=1000;
VAR
    val,down,next,pre:array[0..maxn]of longint;
    dpi:array[0..maxn]of longint;           //dpi信息 以区间内点的个数为例
    Last:array[0..maxlev]of longint;        //last存储搜索过程中在每一层链表里最后访问的节点
    Path:array[1..maxp]of longint;          //path存储搜索路径
    bt:array[1..maxn]of boolean;            //该节点是否为某块的顶部节点 用于判断横向的实边
    SLSize,PathSize:longint;
    op,u,v,right:longint;
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
    	val[maxn]:=inf;
        dpi[maxn]:=0;
        for i:=0 to maxlev do
        begin
        	val[i]:=-inf;
            down[i]:=i-1;
            next[i]:=maxn;
            pre[i]:=none;
            dpi[i]:=0;
        end;
        down[0]:=none;
        SLSize:=maxlev;
    End;
    Function search(v:longint):longint;     //搜索v
    Var
    	p,lv:longint;
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
    Procedure update(v:longint);
    Var
        i,p:longint;
    Begin
        search(v);
        for i:=PathSize-1 downto 1 do
        begin
        	p:=Path[i];
            dpi[p]:=dpi[down[p]];
            if bt[next[p]] then
                dpi[p]:=dpi[p]+dpi[next[p]];
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
            writeln('ERROR!');
        	exit;
        end;
        dpi[SLSize+1]:=1;
        for i:=0 to h do
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
        update(v);
        update(v-1);
        writeln('Done');
    End;
    Procedure delete(v:longint);            //删除
    Var
    	i,p:longint;
    Begin
    	if val[search(v)]<>v then
        begin
            writeln('ERROR!');
        	exit;
        end;
        for i:=0 to maxlev do
        begin
        	if val[last[i]]<>v then break;
            p:=pre[last[i]];
            next[p]:=next[next[p]];
            pre[next[p]]:=p;
        end;
        update(v);
        writeln('Done');
    End;
    Function ask(p,l,r:longint):longint;    //询问在以p为根节点的子树中 有多少个数属于[l,r)
    Begin
        ask:=0;
        if (val[p]>=l)and(right<=r) then exit(dpi[p]);
        if (val[p]>=r)or (right<=l) then exit(0);
        if down[p]=none then
        begin
            if val[p]>=l then exit(1);
            exit(0);
        end;
        if bt[next[p]] then ask:=ask(next[p],l,r);
        right:=val[next[p]];
        ask:=ask+ask(down[p],l,r);
    End;
BEGIN
	randomize;
    init;
    while not eof do
    begin
        read(op,u);   //输入两个数字 第一个数字表示操作 第二个数字表示需要操作的值
        if op=1 then writeln('Found ',val[search(u)]);
        if op=2 then insert(u);
        if op=3 then delete(u);
        if op=4 then
        begin
            read(v);
            right:=inf;
            writeln('Found ',ask(maxlev,u,v),' answers in[',u,',',v,')');
        end;
    end;
    writeln(SLSize);
END.
