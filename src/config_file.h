#pragma once

#include "PathLib_export.h"
#include <QStringList>
#include <QBitArray>

class QSettings;

/// @brief Handles the information stored in the application configuration file
///
/// The configuration file contains the following information:
/// - Paths    : The list of paths to be shown in the application (could not be the same than
///              the stored in the windows registry)
/// - Statuses : A list of boolean values indicating if each of the paths is enabled or not. For
///              a path, to be enabled means that it will be stored in the registry. If a path is
///              disabled will not be stored in the registry. In that way we can keep paths in the
///              application and enable/disabled them when needed.
/// - Order    : A list with values indicating the order for each of the paths. In case that the
///              PATH environment variable has been edited by other software or manually, we need
///              to keep this information in order to be independent from other applications.
class PATHLIB_EXPORT ConfigFile
{
public:
    ConfigFile(const QString &appName);
    ~ConfigFile();

    // --------------------------------------------------------------------------------------------
    // Accessors / Getters
    // --------------------------------------------------------------------------------------------

    /// @brief Gets the list of paths.
    QStringList getPaths() const;

    /// @brief Gets the array of statuses for each path.
    QList<int>   getStatus() const;

    /// @brief Gets the order for each path in which they should be shown in the UI.
    QList<int>  getOrder() const;

    /// @brief Gets the absolute file path of the file in which the configuration is saved.
    QString     filePath() const;

    // --------------------------------------------------------------------------------------------
    // Mutators / Setters
    // --------------------------------------------------------------------------------------------

    /// @brief Writes the list of paths.
    void setPaths(const QStringList &paths);

    /// @brief Writes the list of statuses for each path.
    void setStatus(const QList<int> &status);

    /// @brief Writes the order configured for each path.
    void setOrder(const QList<int> &order);

private:
    QSettings* m_settings;
};
