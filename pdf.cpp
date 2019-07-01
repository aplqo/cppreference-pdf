#include<string>
#include<filesystem>
#include<iostream>
#include<wkhtmltox/pdf.h>
#include"list.h"
#include"time.h"
#include"log.h"

using std::string;
using std::cout;
using std::filesystem::path;

namespace doc
{
    static const char *t;
    void add(const path &p,void *par)
    {
        wkhtmltopdf_converter *c=reinterpret_cast<wkhtmltopdf_converter*>(par);
        wkhtmltopdf_object_settings *os=wkhtmltopdf_create_object_settings();
        wkhtmltopdf_set_object_setting(os,"page",p.c_str());
        wkhtmltopdf_set_object_setting(os,"load.stopSlowScript","false");
        wkhtmltopdf_set_object_setting(os,"load.jsdelay",t);
        wkhtmltopdf_add_object(c,os,nullptr);
    }
    /*---callbacks for wkhtmltopdf--- */
    void progress_changed(wkhtmltopdf_converter * c, int p)
    {
        cout<<p<<"\r";
        cout.flush();
    }
    void phase_changed(wkhtmltopdf_converter * c)
    {
        int phase = wkhtmltopdf_current_phase(c);
        info(wkhtmltopdf_phase_description(c,phase));
    }
    void err(wkhtmltopdf_converter * c, const char * msg)
    {
        error(msg);
    }
    void warn(wkhtmltopdf_converter * c, const char * msg)
    {
        warning(msg);
    }

    inline bool generate(list &l,const char *out)
    {   
        wkhtmltopdf_global_settings *gs=wkhtmltopdf_create_global_settings();
        wkhtmltopdf_set_global_setting(gs,"out",out);
        
        wkhtmltopdf_converter *c=wkhtmltopdf_create_converter(gs);
        l.Apply(add,c);

        wkhtmltopdf_set_phase_changed_callback(c,phase_changed);
        wkhtmltopdf_set_progress_changed_callback(c,progress_changed);
        wkhtmltopdf_set_error_callback(c,err);
        wkhtmltopdf_set_warning_callback(c,warn);

        bool result=wkhtmltopdf_convert(c);
        wkhtmltopdf_destroy_converter(c);
        wkhtmltopdf_destroy_global_settings(gs);
        return result;
    }
    void pdf(list &l,const char *out)
    {
        wkhtmltopdf_init(false);

        info("Measuring jsdelay time...");
        {
            string s=time(l);
            t=s.c_str();
        }
        info("Generating pdf...");
        if(!generate(l,out))
        {
            error("Failed to generate pdf file");
            exit(-1);
        }
        wkhtmltopdf_deinit();
    }
}