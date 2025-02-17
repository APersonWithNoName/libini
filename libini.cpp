#include "libini.hpp"


libini::_Section::_Section(const std::string& secName)
{
    this->_Name = secName;
}

bool libini::_Section::isNodeExist(const std::string& nodKey)
{
    if (nodKey == this->_Data.end()->first)
    {
        return true;
    }
    else
    {
        if (this->_Data.find(nodKey) == this->_Data.end())
            return false;
        else
            return true;
    }
}

bool libini::_Section::addNode(const std::string& nodKey, const std::string& nodValue)
{
    if(this->isNodeExist(nodKey))
    {
        INI_ERROR("Node exists.")
        return false;
    }
    else{
        this->_Data[nodKey]._Value = nodValue;
        return true;
    }
}

void libini::_Section::appendSection(_Section& sec)
{
    this->_Data.insert(sec._Data.begin(), sec._Data.end());
}

void libini::_Section::setNode(const std::string& nodKey, const std::string& nodValue)
{
    if(this->isNodeExist(nodKey))
    {
        this->_Data[nodKey]._Value = nodValue;
    }
    else
    {
        this->addNode(nodKey, nodValue);
    }
}

void libini::_Section::rename(const std::string& newName)
{
    this->_Name = newName;
}

std::string libini::_Section::getName(void)
{
    return this->_Name;
}

std::string libini::_Section::getValue(const std::string& nodKey)
{
    if(this->isNodeExist(nodKey))
    {
        return this->_Data.at(nodKey)._Value;
    }
    else
    {
        INI_ERROR("Node Not Exist.")
        return "";
    }
}

std::vector<std::string> libini::_Section::getAllKeys(void)
{
    std::vector<std::string> result;
    for (std::map<std::string, libini::_Node>::iterator i = this->_Data.begin(); i != this->_Data.end(); i++)
    {
        result.push_back(i->first);
    }
    return result;
}

bool libini::_Section::removeNode(const std::string& nodKey)
{
    if(this->isNodeExist(nodKey))
    {
        this->_Data.erase(nodKey);
        return true;
    }
    else
    {
        INI_ERROR("Node Not exist.")
        return false;
    }
}

void libini::_Section::clear(void)
{
    this->_Data.clear();
}

std::string libini::_Section::toString(void)
{   
    std::string Result;
    if(this->_Name == ""){
        Result = "";
    }
    else{
        Result = "[" + this->_Name + "]\n";
    }
    for (std::map<std::string, libini::_Node>::iterator i = this->_Data.begin(); i != this->_Data.end(); i++)
    {
        Result += i->first + "=" + i->second._Value + "\n";
    }
    return Result;
}


libini::ini::ini()
{
  this->_FileName = "";
}

libini::ini::ini(const std::string& FileName)
{
    this->_FileName = FileName;
}

bool libini::ini::isSectionExist(const std::string& secName)
{
    if (secName == this->_Data.end()->first)
    {
        return true;
    }
    else
    {
        if (this->_Data.find(secName) == this->_Data.end())
            return false;
        else
            return true;
    }
}

void libini::ini::addSection(_Section &sec)
{
    this->_Data.emplace(sec.getName(), sec);
}

void libini::ini::add(const std::string& secName, const std::string& nodKey, const std::string& nodValue)
{
    if(!this->isSectionExist(secName))
    {
        _Section sec(secName);
        this->addSection(sec);
    }
    this->_Data.at(secName).addNode(nodKey, nodValue);
}

void libini::ini::add(const std::string& nodKey, const std::string& nodValue)
{
    this->add("", nodKey, nodValue);
}

void libini::ini::set(const std::string& secName, const std::string& nodKey, const std::string& nodValue)
{
   if(!this->isSectionExist(secName))
    {
        _Section sec(secName);
        this->addSection(sec);
    }
    this->_Data.at(secName).setNode(nodKey, nodValue);
}

void libini::ini::set(const std::string& nodKey, const std::string& nodValue)
{
    this->set("", nodKey, nodValue);
}

void libini::ini::append(ini& iniIn)
{
    this->_Data.insert(iniIn._Data.begin(), iniIn._Data.end());
}

void libini::ini::appendSection(_Section& sec)
{
    std::string secName = sec.getName();
    if(this->isSectionExist(secName))
    {
        this->_Data.at(secName).appendSection(sec);
    }
    else
    {
        this->addSection(sec);
    }
}

libini::_Section* libini::ini::getSection(const std::string& secName){
    if(this->isSectionExist(secName))
    {
        return &(this->_Data.at(secName));
    }
    else{
        INI_ERROR("Section Not Exist.")
        return NULL;
    }
}

std::string libini::ini::getValue(const std::string& secName, const std::string& nodKey)
{
    if(this->isSectionExist(secName))
    {
        return this->_Data.at(secName).getValue(nodKey);
    }
    else
    {
        INI_ERROR("Section Not Exist.")
        return "";
    }
}

std::string libini::ini::getValue(const std::string& nodKey)
{
    return this->getValue("", nodKey);
}

std::vector<std::string> libini::ini::getAllSection(void)
{
    std::vector<std::string> result;
    for (std::map<std::string, libini::_Section>::iterator i = this->_Data.begin(); i != this->_Data.end(); i++)
    {
        result.push_back(i->first);
    }
    return result;
}

bool libini::ini::removeNode(const std::string& secName, const std::string& nodKey)
{
    if(this->isSectionExist(secName))
    {
        return this->_Data.at(secName).removeNode(nodKey);
    }
    else{
        INI_ERROR("Section Not Exist.")
        return false;
    }
}

bool libini::ini::removeNode(const std::string& nodKey)
{
    return this->removeNode("", nodKey);
}

bool libini::ini::removeSection(const std::string& secName)
{
    if(this->isSectionExist(secName))
    {
        this->_Data.at(secName).clear();
        return true;
    }
    else{
        INI_ERROR("Section Not Exist.")
        return false;
    }
}

void libini::ini::clear(void)
{
    this->_Data.clear();
}

bool libini::ini::filter(const std::string& input)
{
    if(input.length() == 0 || \
        input[0] == ';' || \
        input[0] == '\n' || \
        input[0] == '\0'
        )
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string libini::ini::LineFilter(const std::string& input)
{
    std::string output;
    for(int i = 0; i < input.length(); i ++)
    {
        if(input[i] == ';')
        {
            break;
        }
        else
        {
            output += input[i];
        }
    }
    return output;
}

int libini::ini::parser(const std::string& FileName)
{
    std::fstream IniFile;
    IniFile.open(FileName, std::ifstream::in | std::ifstream::out | std::fstream::app);

    if(!IniFile.is_open())
    {
        INI_ERROR("Cannot open file!")
        return 1;
    }

    std::string data, secName = "", key, value;
    _Section sec("");
    int line = 1;

    while(!IniFile.eof())
    {
        data.clear();
        key.clear();
        value.clear();

        std::getline(IniFile, data);
        data = LineFilter(data);
        unsigned int LineLength = data.length();

        if(filter(data))
        {
            line ++;
            continue;
        }
        if(data[0] == '[')
        {
            if(data.find(']') == std::string::npos)
            {
                INI_ERROR("Miss \']\'")
                return 2;
            }

            secName.clear();

            for(int i = 1; i < LineLength; i ++)
            {
                if(data[i] == ']')
                {
                    break;
                }
                else{
                    secName += data[i];
                }
            }

            sec.rename(secName);
        }
        else
        {
            if(data.find('=') == std::string::npos)
            {
                INI_ERROR("Miss \'=\'")
                return 4;
            }

            for(int i = 0; i < LineLength; i ++)
            {
                if(data[i] != '=')
                {
                    key += data[i];
                }
                if(data[i] == '=')
                {
                    for(int j = i + 1; j < LineLength; j ++)
                    {
                        value += data[j];
                    }
                    break;
                }
            }
            this->set(secName, key, value);
        }
        line ++;
    }

    IniFile.close();
    IniFile.clear();
    return 0;
}

std::string libini::ini::toString(void)
{
    std::string result;
    for (std::map<std::string, libini::_Section>::iterator i = this->_Data.begin(); i != this->_Data.end(); i++)
    {
        result += i->second.toString() + "\n";
    }
    return result;
}

bool libini::ini::write(const std::string& FileName)
{
    std::string _FileName = this->_FileName;

    if(FileName != "")
    {
        _FileName = FileName;
    }

    std::fstream OutFile;
    OutFile.open(_FileName, std::ifstream::in | std::ifstream::out | std::fstream::app);
    if(!OutFile.is_open())
    {
        return false;
    }
    OutFile << this->toString() << std::endl;
    OutFile.close();
    OutFile.clear();

    return true;
}
