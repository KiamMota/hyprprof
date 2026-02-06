#ifndef BACKUP_HELPER_HPP
#define BACKUP_HELPER_HPP

#include <string>
namespace core {

/**
 * @brief Utility class for managing backups and registering them in a meta JSON.
 * 
 * BackupHelper provides static methods to create backups of files or directories
 * and to record metadata about these backups in a JSON file. This allows
 * tracking of original sources and ensures that backups are organized and
 * reproducible.
 * 
 * The class is fully static and cannot be instantiated.
 */
class BackupHelper
{
private:
    /**
     * @brief Private constructor to prevent instantiation.
     */
    BackupHelper();

    /**
     * @brief Inserts a JSON string into the meta JSON file.
     * 
     * This is used internally to update the meta JSON with new backup entries.
     * 
     * @param content The JSON content to insert.
     */
    static void meta_json_insert(const std::string& content);

    /**
     * @brief Writes a new entry in the meta JSON for a backup.
     * 
     * Each entry contains the backup path name and the original source path.
     * 
     * @param path_name The name or identifier of the backup path.
     * @param original_src The original path of the file or directory being backed up.
     */
    static void write_in_metajson(const std::string& path_name, const std::string& original_src);

public:
    /**
     * @brief Returns the absolute path to the meta JSON file.
     * 
     * @return std::string The path to the meta JSON.
     */
    static const std::string meta_json_path() noexcept;

    /**
     * @brief Returns the current content of the meta JSON file.
     * 
     * @return std::string The content of the meta JSON as a string.
     */
    static const std::string meta_json_content();

    /**
     * @brief Creates a backup of the given source path and registers it in the meta JSON.
     * 
     * This method copies the source directory or file to a backup location and
     * records the original source in the meta JSON for traceability.
     * 
     * @param src_path The source file or directory to back up.
     */
    static void create_copy_backup_path_and_register_in_meta_json(const std::string& path_name, const std::string& original_path);
};

} // namespace core
#endif // BACKUP_HELPER_HPP
