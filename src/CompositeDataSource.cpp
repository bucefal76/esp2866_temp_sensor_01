#include "CompositeDataSource.hpp"

String CompositeDataSource::getDataString()
{

    String url = "";

    uint32_t i = 0;

    for (std::vector<DataSourceIf *>::iterator it = m_DataSources.begin(); it != m_DataSources.end(); it++)
    {
        url += "module";
        url += String(i + 1);
        url += "=";
        url += (*it)->getDataString();

        if (i < getNumberOfSources() - 1)
        {
            url += "&";
        }

        i++;
    }

    return url;
}

bool CompositeDataSource::initializeDataSource()
{
    for (std::vector<DataSourceIf *>::iterator it = m_DataSources.begin(); it != m_DataSources.end(); it++)
    {
        if ((*it)->initializeDataSource() == false)
        {
            return false;
        }
    }

    return true;
}

void CompositeDataSource::addDataSource(DataSourceIf *pDataSource)
{
    m_DataSources.push_back(pDataSource);
}

uint32_t CompositeDataSource::getNumberOfSources() const
{
    return m_DataSources.size();
}