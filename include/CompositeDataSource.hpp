#ifndef COMPOSITE_DATA_SOURCE_HPP
#define COMPOSITE_DATA_SOURCE_HPP

#include "DataSourceIf.hpp"
#include <vector>

class CompositeDataSource : public DataSourceIf
{
public:
    /// @brief See DataSourceIf
    virtual String getDataString() override;
    /// @brief See DataSourceIf
    virtual bool initializeDataSource() override;
    /// @brief Add DataSourceIf to composite structure
    void addDataSource(DataSourceIf *pDataSource);
    /// @brief Get number of added DataSourceIf objects.
    uint32_t getNumberOfSources() const;

private:
    std::vector<DataSourceIf *> m_DataSources;
};

#endif