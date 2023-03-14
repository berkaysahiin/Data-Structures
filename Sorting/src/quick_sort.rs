pub fn quick_sort(list: &mut Vec<i32>, start: isize, end: isize) {
    if end <= start { 
        return 
    };

    let pivot = partition(list, start, end);
    quick_sort(list, start, pivot -1);
    quick_sort(list, pivot + 1, end);
}

fn partition(list: &mut Vec<i32>, start: isize, end: isize) -> isize {
    let pivot = list[end as usize];
    let mut i = start - 1;

    for j in start..end {
        if list[j as usize] < pivot {
            i += 1;
            list.swap(i as usize,j as usize);
        }
    }

    i += 1;
    list.swap(i as usize,end as usize);

    i 
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_quick_sort_with_partially_sorted_vec() {
        let mut vec = vec![5, 2, 9, 1, 7, 6, 8, 3, 4];
        let n = vec.len() as isize;
        quick_sort(&mut vec, 4, n - 1);
        assert_eq!(vec, vec![5, 2, 9, 1, 3, 4, 6, 7, 8]);
    }

    #[test]
    fn test_quick_sort_with_duplicate_elements() {
        let mut vec = vec![5, 2, 9, 1, 7, 2, 8, 3, 4];
        let n = vec.len() as isize;
        quick_sort(&mut vec, 0, n - 1);
        assert_eq!(vec, vec![1, 2, 2, 3, 4, 5, 7, 8, 9]);
    }

    #[test]
    fn test_quick_sort_with_negative_elements() {
        let mut vec = vec![-5, -2, -9, 1, -7, 6, -8, 3, 4];
        let n = vec.len() as isize;
        quick_sort(&mut vec, 0, n - 1);
        assert_eq!(vec, vec![-9, -8, -7, -5, -2, 1, 3, 4, 6]);
    }

    #[test]
    fn test_quick_sort_with_random_elements() {
        let mut vec = vec![5, 4, 2, 1, 3, 6, 7, 8, 9];
        let n = vec.len() as isize;
        quick_sort(&mut vec, 0, n - 1);
        assert_eq!(vec, vec![1, 2, 3, 4, 5, 6, 7, 8, 9]);
    }

        #[test]
    fn test_quick_sort_with_all_same_elements() {
        let mut vec = vec![1, 1, 1, 1, 1, 1];
        let n = vec.len() as isize;
        quick_sort(&mut vec, 0, n - 1);
        assert_eq!(vec, vec![1, 1, 1, 1, 1, 1]);
    }

    #[test]
    fn test_quick_sort_with_already_sorted_vec() {
        let mut vec = vec![1, 2, 3, 4, 5, 6, 7, 8, 9];
        let n = vec.len() as isize;
        quick_sort(&mut vec, 0, n - 1);
        assert_eq!(vec, vec![1, 2, 3, 4, 5, 6, 7, 8, 9]);
    }

    #[test]
    fn test_quick_sort_with_reverse_order() {
        let mut vec = vec![9, 8, 7, 6, 5, 4, 3, 2, 1];
        let n = vec.len() as isize;
        quick_sort(&mut vec, 0, n - 1);
        assert_eq!(vec, vec![1, 2, 3, 4, 5, 6, 7, 8, 9]);
    }

    #[test]
    fn test_quick_sort_with_large_input() {
        let mut vec = vec![5, 2, 9, 1, 7, 6, 8, 3, 4, 10, 12, 11, 15, 14, 13, 16, 18, 17, 19, 20];
        let n = vec.len() as isize;
        quick_sort(&mut vec, 0, n - 1);
        assert_eq!(vec, vec![1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]);
    }
}
