
#include "../shell_parser/shell_parser.h"

using namespace std;

int main(int argc, char *args[])
{
    string inf_pname, outfilename, filename;
    inf_pname = string(args[1]);
    outfilename = string(args[2]);
    ifstream inf;
    ofstream ouf;
    inf.open(inf_pname);
    if (!inf)
    {
        cout << "Open error: " << inf_pname << endl;
        return 1;
    }
    ouf.open(outfilename);
    if (!ouf)
    {
        cout << "Open error: " << outfilename << endl;
        return 1;
    }

    vector<string> v_file;
    string buf;
    while (getline(inf, buf))
        v_file.emplace_back(std::move(buf));

    vshell::Shell_parser::outfile_type outf;
    vshell::Shell_parser sh_parser(v_file);
    try
    {
        if (sh_parser.parser(outf) == false)
            return 1;
    }
    catch(...)
    {
        cerr<<"unknown error"<<endl;
        return 2;
    }

    for (const auto &of : outf)
    {
        cout << to_string(of.index) << ": " << of.line << endl;
    }

    inf.close();
    ouf.close();
    return 0;
}