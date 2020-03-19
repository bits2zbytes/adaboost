#ifndef ADABOOST_CORE_OPERATIONS_IMPL_CPP
#define ADABOOST_CORE_OPERATIONS_IMPL_CPP

#include<adaboost/utils/utils.hpp>
#include<adaboost/core/operations.hpp>
#include<iostream>

namespace adaboost
{
    namespace core
    {
        template <class data_type>
        void Sum(
        data_type (*func_ptr)(data_type),
        const Vector<data_type>& vec,
        unsigned start,
        unsigned end,
        data_type& result)
        {
            adaboost::utils::check(vec.get_size() >= start,
            "Start is out of range.");
            end = vec.get_size() - 1 < end ?
                    vec.get_size() - 1 : end;
            result = 0;
            for(unsigned i = start; i <= end; i++)
            {
                result += func_ptr(vec.at(i));
            }
        }

        template <class data_type_1, class data_type_2>
        void Argmax(
        data_type_2 (*func_ptr)(data_type_1),
        const Vector<data_type_1>& vec,
        data_type_1& result)
        {
            data_type_2 max_val = func_ptr(vec.at(0));
            data_type_1 arg_max = vec.at(0);
            for(unsigned i = 0; i < vec.get_size(); i++)
            {
                if(max_val < func_ptr(vec.at(i)))
                {
                    max_val = func_ptr(vec.at(i));
                    arg_max = vec.at(i);
                }
            }
            result = arg_max;
        }

        template <class data_type_vector>
        void fill(data_type_vector value);
        {
            for(unsigned int i = 0; i < this->size; i++)
            {
                this->data[i] = value;
            }
        }


        template <class data_type_matrix>
        void fill(data_type_matrix value);
        {
            for(unsigned int i = 0; i < this->rows; i++)
            {
                for(unsigned int j = 0; j < this->cols; j++)
                {
                    this->data[i*this->cols + j] = value;
                }
            }
        }


        template <class data_type_vector, class data_type_matrix>
        void multiply(const Vector<data_type_vector>& vec,
                     const Matrix<data_type_matrix>& mat,
                     Vector<data_type_vector>& result)
        {
            adaboost::utils::check(vec.get_size() == mat.get_rows(),
                                  "Orders mismatch in the inputs.");
            for(unsigned int j = 0; j < mat.get_cols(); j++)
            {
                data_type_vector _result = 0;
                for(unsigned int i = 0; i < mat.get_rows(); i++)
                {
                    _result += (vec.at(i)*mat.at(i, j));
                }
                result.set(j, _result);
            }
        }

        template <class data_type_matrix>
        void multiply(const Matrix<data_type_matrix>& mat1,
                     const Matrix<data_type_matrix>& mat2,
                     Matrix<data_type_matrix>& result)
        {
            adaboost::utils::check(mat1.get_cols() == mat2.get_rows(),
                                    "Order of matrices don't match.");
            unsigned int common_cols = mat1.get_cols();
            for(unsigned int i = 0; i < result.get_rows(); i++)
            {
                for(unsigned int j = 0; j < result.get_cols(); j++)
                {
                    data_type_matrix _result = 0;
                    for(unsigned int k = 0; k < common_cols; k++)
                    {
                        _result += (mat1.at(i, k)*mat2.at(k, j));
                    }
                    result.set(i, j, _result);
                }
            }
        }

        template <class data_type_vector>
                void product(const Vector<data_type_vector>& vec1,
                             const Vector<data_type_vector>& vec2,
                             data_type_vector& result)
                {
                    adaboost::utils::check(vec1.get_size() == vec2.get_size(),
                                           "Size of vectors don't match.");
                    result = 0;
                    for(unsigned int i = 0; i < vec1.get_size(); i++)
                    {
                        result += (vec1.at(i)*vec2.at(i));
                    }
                }


        #include "instantiated_templates_operations.hpp"

    } // namespace core
} // namespace adaboost

#endif
