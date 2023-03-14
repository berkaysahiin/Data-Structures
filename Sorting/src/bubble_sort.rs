fn bubble_sort(vec: &mut Vec<i32>) {
    if vec.is_empty() {
        return;
    }

    let mut n = vec.len();
    let mut swapped = true;

    while swapped {
        swapped = false;
        for i in 0..n - 1 {
            if vec[i] > vec[i + 1] {
                vec.swap(i, i + 1);
                swapped = true;
            }
        }
        n -= 1;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_bubble_sort_with_small_vec() {
        let mut vec = vec![4, 2, 1, 3];
        bubble_sort(&mut vec);
        assert_eq!(vec, vec![1, 2, 3, 4]);
    }

    #[test]
    fn test_bubble_sort_with_large_vec() {
        let mut vec = vec![5, 2, 9, 1, 7, 6, 8, 3, 4];
        bubble_sort(&mut vec);
        assert_eq!(vec, vec![1, 2, 3, 4, 5, 6, 7, 8, 9]);
    }

    #[test]
    fn test_bubble_sort_with_already_sorted_vec() {
        let mut vec = vec![1, 2, 3, 4, 5, 6, 7, 8, 9];
        bubble_sort(&mut vec);
        assert_eq!(vec, vec![1, 2, 3, 4, 5, 6, 7, 8, 9]);
    }

    #[test]
    fn test_bubble_sort_with_empty_vec() {
        let mut vec = vec![];
        bubble_sort(&mut vec);
        assert_eq!(vec, vec![]);
    }

    #[test]
    fn test_bubble_sort_with_vec_of_one_element() {
        let mut vec = vec![1];
        bubble_sort(&mut vec);
        assert_eq!(vec, vec![1]);
    }

    #[test]
    fn test_bubble_sort_with_duplicate_elements() {
        let mut vec = vec![5, 2, 9, 1, 7, 2, 8, 3, 4];
        bubble_sort(&mut vec);
        assert_eq!(vec, vec![1, 2, 2, 3, 4, 5, 7, 8, 9]);
    }

    #[test]
    fn test_bubble_sort_with_ascending_vec() {
        let mut vec = vec![1,2,3,4,5,6,7,8,9];
        bubble_sort(&mut vec);
        assert_eq!(vec, vec![1, 2, 3, 4, 5, 6, 7, 8, 9]);
    }

    #[test]
    fn test_bubble_sort_with_descending_vec() {
        let mut vec = vec![9,8,7,6,5,4,3,2,1];
        bubble_sort(&mut vec);
        assert_eq!(vec, vec![1, 2, 3, 4, 5, 6, 7, 8, 9]);
    }

    #[test]
    fn test_bubble_sort_with_negative_numbers(){
        let mut vec = vec![-3,5,-6,9,-11,8];
        bubble_sort(&mut vec);
        assert_eq!(vec, vec![-11,-6,-3,5,8,9]);
    }
}

