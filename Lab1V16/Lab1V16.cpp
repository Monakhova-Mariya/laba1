#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

/*!
    \brief Класс, задающий абитуриента
*/
struct enrollee
{
    std::string name; ///< ФИО абитуриента
    std::string faculty; ///< Факультет
    std::string speciality; ///< Специальность
    int result; ///< Количество набранных баллов

    enrollee(std::string name = "", std::string faculty = "", std::string speciality = "", int result = 0)
    {
        this->name = name;
        this->faculty = faculty;
        this->speciality = speciality;
        this->result = result;
    }

    /*!
        Оператор сравнения меньше
        \param[in] right правое сравниваемое значение
        \return Возвращает true, если левый объект строго меньше, false - иначе
    */
    bool operator<(enrollee right)
    {
        if (this->result == right.result)
        {
            if (this->name == right.name)
            {
                if (this->faculty == right.faculty)
                {
                    if (this->speciality == right.speciality)
                        return false;

                    return this->speciality < right.speciality;
                }
                
                return this->faculty < right.faculty;
            }

            return this->name < right.name;
        }
        return this->result > right.result;
    }

    /*!
        Оператор сравнения больше
        \param[in] right правое сравниваемое значение
        \return Возвращает true, если левый объект строго больше, false - иначе
    */
    bool operator>(enrollee right)
    {
        if (this->result == right.result)
        {
            if (this->name == right.name)
            {
                if (this->faculty == right.faculty)
                {
                    if (this->speciality == right.speciality)
                        return false;

                    return this->speciality > right.speciality;
                }

                return this->faculty > right.faculty;
            }

            return this->name > right.name;
        }
        return this->result < right.result;
    }

    /*!
        Оператор сравнения меньше или равно
        \param[in] right правое сравниваемое значение
        \return Возвращает true, если левый объект меньше или равен, false - иначе
    */
    bool operator<=(enrollee right)
    {
        if (this->result == right.result)
        {
            if (this->name == right.name)
            {
                if (this->faculty == right.faculty)
                {
                    if (this->speciality == right.speciality)
                        return true;

                    return this->speciality < right.speciality;
                }

                return this->faculty < right.faculty;
            }

            return this->name < right.name;
        }
        return this->result > right.result;
    }

    /*!
        Оператор сравнения больше или равно
        \param[in] right правое сравниваемое значение
        \return Возвращает true, если левый объект больше или равен, false - иначе
    */
    bool operator>=(enrollee right)
    {
        if (this->result == right.result)
        {
            if (this->name == right.name)
            {
                if (this->faculty == right.faculty)
                {
                    if (this->speciality == right.speciality)
                        return true;

                    return this->speciality > right.speciality;
                }

                return this->faculty > right.faculty;
            }

            return this->name > right.name;
        }
        return this->result < right.result;
    }
};


/*!
    \brief Класс, содержащий реализуемые сортировки
*/
template<typename T>
class sorts
{
public:

    /*!
        Сортировка выбором
        \param[in] data Сортируемый массив
        \param[in] n Число элементов в массиве
    */
    static void selectionSort(T* data, int n)
    {
        for (int i = 0; i < n; i++)
        {
            int min = i;

            for (int j = i + 1; j < n; j++)
            {
                if (data[min] > data[j]) min = j;
            }

            T temp = data[min];
            data[min] = data[i];
            data[i] = temp;
        }
    }

    /*!
        Интерфейс для сортировки слиянием
        \param[in] data Сортируемый массив
        \param[in] n Число элементов в массиве
    */
    static void mergeSort(T* data, int n)
    {
        nowMerge(data, 0, n - 1);
    }

    /*!
        Интерфейс для сортировки кучей
        \param[in] data Сортируемый массив
        \param[in] n Число элементов в массиве
    */
    static void heapSort(T* data, int n)
    {
        for (int i = n / 2 - 1; i >= 0; i--)
        {
            downHeap(data, i, n);
        }

        for (int i = n - 1; i > 0; i--)
        {
            T temp = data[i];
            data[i] = data[0];
            data[0] = temp;
            downHeap(data, 0, i);
        }
    }

private:

    /*!
        Сортировка слиянием
        \param[in] data Сортируемый массив
        \param[in] start Индекс первого сортируемого элемента
        \param[in] end Индекс последнего сортируемого элемента
    */
    static void nowMerge(T* data, int start, int end)
    {
        if (start == end)
            return;

        nowMerge(data, start, (start + end) / 2);
        nowMerge(data, (start + end) / 2 + 1, end);

        merge(data, start, (start + end) / 2, end);
    }

    /*!
        Слияние массивов
        \param[in] data Сортируемый массив
        \param[in] start Индекс начала первого сливаемого отрезка
        \param[in] mid Индекс конца первого сливаемого отрезка
        \param[in] end Индекс конца последнего сливаемого отрезка
    */
    static void merge(T* data, int start, int mid, int end)
    {
        int i = start;
        int j = mid + 1;

        T* temp = new T[end - start + 1];

        int k = 0;

        while (i <= mid && j <= end)
        {
            if (data[i] < data[j])
            {
                temp[k] = data[i];
                i++;
            }
            else
            {
                temp[k] = data[j];
                j++;
            }

            k++;
        }

        while (i <= mid)
        {
            temp[k] = data[i];
            i++;
            k++;
        }

        while (j <= end)
        {
            temp[k] = data[j];
            j++;
            k++;
        }

        for (int i = 0; i < end - start + 1; i++)
            data[i + start] = temp[i];
    }

    /*!
        Создание пирамиды
        \param[in] data Сортируемый массив
        \param[in] start Индекс текущего элемента
        \param[in] n Число элементов в массиве
    */
    static void downHeap(T* data, int start, int n)
    {
        T now_elem = data[start];
        int child = 2 * start + 1;
        if (child < n - 1 && data[child] < data[child + 1])
            child++;

        if (now_elem < data[child])
        {
            data[start] = data[child];
            data[child] = now_elem;

            if (2 * child + 1 < n)
                downHeap(data, child, n);
        }
    }
};


int main()
{
    int sizes[10] = {100, 1000, 5000, 10000, 20000, 30000, 40000, 50000, 75000, 100000};

    for (int size : sizes)
    {
        {
            std::ifstream in;
            char filename[80];
            memset(filename, 0, 80);
            sprintf_s(filename, "%s%d%s", "data_", size, ".txt");

            in.open(filename);

            enrollee* data = new enrollee[size];

            for (int i = 0; i < size; i++)
            {
                std::string name, faculty, speciality;
                int result;
                in >> name >> faculty >> speciality >> result;
                data[i] = enrollee(name, faculty, speciality, result);
            }

            in.close();

            auto begin = std::chrono::high_resolution_clock::now();

            sorts<enrollee>::mergeSort(data, size);

            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "Merge sort " << size << " elements " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

            std::ofstream out;
            memset(filename, 0, 80);
            sprintf_s(filename, "%s%d%s", "Merge sort\\data_", size, ".csv");
            out.open(filename);


            out << "ФИО;Факультет;Специальность;Число баллов" << '\n';

            for (int i = 0; i < size; i++)
            {
                out << data[i].name << ";" << data[i].faculty << ";" << data[i].speciality << ";" << data[i].result << '\n';
            }

            out.close();
        }
    }

    for (int size : sizes)
    {
        {
            std::ifstream in;
            char filename[80];
            memset(filename, 0, 80);
            sprintf_s(filename, "%s%d%s", "data_", size, ".txt");

            in.open(filename);

            enrollee* data = new enrollee[size];

            for (int i = 0; i < size; i++)
            {
                std::string name, faculty, speciality;
                int result;
                in >> name >> faculty >> speciality >> result;
                data[i] = enrollee(name, faculty, speciality, result);
            }

            in.close();

            auto begin = std::chrono::high_resolution_clock::now();

            sorts<enrollee>::heapSort(data, size);

            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "Heap sort " << size << " elements " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

            std::ofstream out;
            memset(filename, 0, 80);
            sprintf_s(filename, "%s%d%s", "Heap sort\\data_", size, ".csv");
            out.open(filename);


            out << "ФИО;Факультет;Специальность;Число баллов" << '\n';

            for (int i = 0; i < size; i++)
            {
                out << data[i].name << ";" << data[i].faculty << ";" << data[i].speciality << ";" << data[i].result << '\n';
            }

            out.close();
        }
    }

    for (int size : sizes)
    {
        {
            std::ifstream in;
            char filename[80];
            memset(filename, 0, 80);
            sprintf_s(filename, "%s%d%s", "data_", size, ".txt");

            in.open(filename);

            enrollee* data = new enrollee[size];

            for (int i = 0; i < size; i++)
            {
                std::string name, faculty, speciality;
                int result;
                in >> name >> faculty >> speciality >> result;
                data[i] = enrollee(name, faculty, speciality, result);
            }

            in.close();

            auto begin = std::chrono::high_resolution_clock::now();

            sorts<enrollee>::selectionSort(data, size);

            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "Selection sort " << size << " elements " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

            std::ofstream out;
            memset(filename, 0, 80);
            sprintf_s(filename, "%s%d%s", "Selection sort\\data_", size, ".csv");
            out.open(filename);


            out << "ФИО;Факультет;Специальность;Число баллов" << '\n';

            for (int i = 0; i < size; i++)
            {
                out << data[i].name << ";" << data[i].faculty << ";" << data[i].speciality << ";" << data[i].result << '\n';
            }

            out.close();
        }
    }
}


/*Генерация данных

std::string genStr()
{
    int length = rand() % 50 + 10;
    std::string result = "";

    for (int i = 0; i < length; i++)
    {
        result.append(1, (rand() % ('Z' - 'A' + 1)) + 'A');
    }

    return result;
}


int main()
{
    int sizes[10] = { 100, 1000, 5000, 10000, 20000, 30000, 40000, 50000, 75000, 100000 };

    for (int size : sizes)
    {
        std::ofstream out;
        char filename[80];
        memset(filename, 0, 80);
        sprintf_s(filename, "%s%d%s", "data_", size, ".txt");

        out.open(filename);

        for (int i = 0; i < size; i++)
        {
            out << genStr() << " " << genStr() << " " << genStr() << " " << rand() % 310 << std::endl;
        }

        out.close();
    }
}*/

