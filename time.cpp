#include<list>
#include"list.h"
#include<charconv>
#include<filesystem>
#include<string>
#include<wkhtmltox/pdf.h>

using std::to_chars;
using std::string;
namespace fs=std::filesystem;
using fs::file_size;
using fs::path;
using fs::remove;
using fs::create_directory;
using fs::exists;

namespace doc
{
    const path tmpdir("/tmp/cppreference-doc");
    /* 
    //callback functions for wkhtmltopdf
    void progress_changed(wkhtmltopdf_converter *c,int p){}
    void phase_changed(wkhtmltopdf_converter *c){}
    void error(wkhtmltopdf_converter *c,const char *msg){}
    void warning(wkhtmltopdf_converter *c,const char *msg){}*/

    struct range
    {
        unsigned int beg;
        unsigned int end;
        uintmax_t size;
    };
    struct file
    {
        uintmax_t size;
        path pa;
    };
    uintmax_t tryone(const path &p,unsigned int time)
    {
        path out=tmpdir/p.filename();
        uintmax_t result;

        wkhtmltopdf_global_settings *gs=wkhtmltopdf_create_global_settings();
        wkhtmltopdf_set_global_setting(gs,"out",out.c_str());

        wkhtmltopdf_object_settings *os=wkhtmltopdf_create_object_settings();
        wkhtmltopdf_set_object_setting(os,"page",p.c_str());
        wkhtmltopdf_set_object_setting(os,"load.stopSolwScript","false");
        char t[3];
        to_chars(t,t+3,time);
        wkhtmltopdf_set_object_setting(os,"load.jsdelay",t);

        wkhtmltopdf_converter *c=wkhtmltopdf_create_converter(gs);
        wkhtmltopdf_add_object(c,os,nullptr);

        wkhtmltopdf_convert(c);
        wkhtmltopdf_destroy_converter(c);

        if(!exists(out))
        {
            return 0;
        }
        result=file_size(out);
        remove(out);
        return result;
    }
    unsigned int find(const path &p,const range &r,unsigned int times=0)
    {
        if(times>4)
        {
            return r.end;
        }
        unsigned int mid=(r.beg+r.end)/2;
        uintmax_t mids=tryone(p,mid);
        if(mids<r.size)
        {
            return find(p,{mid,r.end,r.size},times++);
        }
        else
        {
            return find(p,{r.beg,mid,r.size},times++);
        }
    }
    inline range getr(const path &p)
    {
        range result{200,200,0};
        result.size=tryone(p,200);
        unsigned int tmp=200;
        uintmax_t size=result.size;
        while(true)
        {
            tmp+=50;
            size=tryone(p,tmp);
            if(size>result.size)
            {
                result.end=tmp;
                result.size=size;
            }
            else
            {
                break;
            }
        }
        while(true)
        {
            tmp-=50;
            size=tryone(p,tmp);
            result.beg=tmp;
            if(size<result.size)
            {
                break;
            }
            else
            {
                result.end=tmp;
            }
        }
        return result;
    }
    void sort(const path &p,void *par)
    {
        std::list<file>* lst=reinterpret_cast<std::list<file>*>(par);
        uintmax_t size=file_size(p);
        if(size<(lst->end()--)->size)
        {
            return;
        }
        std::list<file>::iterator it=lst->begin();
        for(unsigned int i=0;i<5;i++,it++)
        {
            if(size>it->size)
            {
                lst->insert(it--,{size,p});
            }
        }
        return;
    }
    inline void getlarge(list &l,path p[])
    {
        std::list<file> lst;
        l.Apply(sort,&lst);
        std::list<file>::iterator it=lst.begin();
        for(unsigned int i=0;i<5;i++,it++)
        {
            p[i]=it->pa;
        }
    }
    string time(list &l)
    {
        unsigned int tim[5];
        {
            path f[5];
            getlarge(l,f);
            for(unsigned int i=0;i<5;i++)
            {
                range r=getr(f[i]);
                tim[i]=find(f[i],r);
            }
        }
        unsigned int res;
        for(auto i:tim)
        {
            res+=i;
        }
        res/=5;
        res+=10;
        char ch[3];
        to_chars(ch,ch+3,res);
        return string(ch);
    }
}