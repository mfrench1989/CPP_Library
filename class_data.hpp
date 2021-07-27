#ifndef CLASSDATA_HPP
#define CLASSDATA_HPP

#include <string>
#include <vector>

class ClassData {

public:
  ClassData();

  /**
   * @brief dataClear - clear stored data
   */
  void dataClear();

  /**
   * @brief dataPush - push data to Vector_Data
   * @param string - label of stored data
   * @param vector<char> - data vector of bytes
   */
  void dataPush(const std::string&, const std::vector<char>&);

  /**
   * @brief dataIndex - get index of data label
   * @param string - label of stored data
   * @return
   */
  int dataIndex(const std::string&);

  /**
   * @brief dataLabel - get label of data at index
   * @param int - index of stored data
   * @return
   */
  std::string dataLabel(const int);

  /**
   * @brief dataBytes - get data bytes of data at index
   * @param int - index of stored data
   * @return
   */
  std::vector<char> dataBytes(const int);

  /**
   * @brief dataBytes - get data bytes of data label
   * @param string - label of stored data
   * @return
   */
  std::vector<char> dataBytes(const std::string&);
  /**
   * @brief dataList - get list of all data labels
   * @return
   */
  std::vector<std::string> dataList();

private:
  struct Data {
    std::string Label = "";
    std::vector<char> Bytes = std::vector<char>();
  };
  std::vector<Data> Vector_Data;
};

#endif // CLASSDATA_HPP
