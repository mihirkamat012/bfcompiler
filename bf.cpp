
#include<iostream>
#include<string>
const char* prog;
unsigned char mem[300];

int stack[300];
int progpos;
int stacktop;
int ptr;
void init()
{
    progpos=0;
    stacktop=-1;
    ptr=0;
    int i=0;
    while(i<300)
    {
        
        mem[i]=0;
        stack[i]=-1;
        i++;
    }
}
void oper(char c)
{
    if(c=='>')
    {
        std::cout<<"movup\n";
        ptr++;
        progpos++;
    }
    else if(c=='<'&&ptr>0){
        std::cout<<"movdown\n";
        ptr--;
        progpos++;
    }
    else if(c=='+'&&mem[ptr]<256)
    {
        std::cout<<"incr\n";
        mem[ptr]++;
        progpos++;
    }
    else if(c=='-'&&mem[ptr]>=0)
    {
        std::cout<<"decr\n";
        mem[ptr]--;
        progpos++;
    }
    else if(c=='.')
    {
        std::cout<<"\tout: ";
        std::cout<<mem[ptr]<<"\n";
        progpos++;
    }
    else if(c==',')
    {
        std::cout<<"in: ";
        int n=0;
        scanf("%d",&n);
        
        if(n>=0&&n<256){
        std::cout<<"value: "<<n<<" \n";
        mem[ptr]=(char)n;
        }
        else
        std::cout<<"err: defaulted to 0.\n";

        progpos++;
    }
    else if(c=='[')
    {
        if(mem[ptr]!=0)
        {
            std::cout<<"loop enter\n";
            stacktop++;
            stack[stacktop]=progpos;
        }
        progpos++;       
    }
    else if(c==']')
    {
         if(mem[ptr]==0)
        {
            std::cout<<"loop exit\n";
            stack[stacktop]=-1;
            stacktop--;
            progpos++;
        }
        else
        progpos=stack[stacktop]+1;
        std::cout<<"pos at "<<progpos<<"\n";
    }
    else return;
}
int main(int argc, char** argv)
{
   // prog="+++++>+++++++>+[>+++>+++<---]+++>++++--";
    
    if(argc==2)
    {
        init();
        prog=argv[1];
        while(prog[progpos]!='\0')
        {
            std::cout<<"char "<<progpos<<" : ";
            oper(prog[progpos]);
        }
    }
    else
    {
        init();
        while(1)
        {
            std::cout<<"\n~~: ";
            std::string prg;
            std::cin>>prg;
            prog=prg.c_str();
            if(prg.length()==1&&(prg[0]=='x'||prg[0]=='X'))
            {
                std::cout<<"exiting...\n";
                return 0;
            }
            else
            {
                
                while(prog[progpos]!='\0')
                {
                    std::cout<<"char "<<progpos<<" : ";
                    oper(prog[progpos]);
                }   
            }
        }
    }
}