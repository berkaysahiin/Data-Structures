pub fn merge_sort(list: &mut Vec<i32>, start:usize, end: usize) {
    let len = end - start;

    if len <= 1 {
        return;
    }

    let mid = (start + end) / 2;

    merge_sort(list, start, mid);
    merge_sort(list, mid, end);
    merge(list, start, mid, end);
}

fn merge(list: &mut Vec<i32>, start: usize, mid: usize, end: usize) {
    let mut i = start;
    let mut j = mid;
    let mut merged = vec![];

    while i < mid && j < end {
        if list[i] <= list[j] {
            merged.push(list[i]);
            i += 1;
        } else {
            merged.push(list[j]);
            j += 1;
        }
    }

    while i < mid {
        merged.push(list[i]);
        i += 1;
    }

    while j < end {
        merged.push(list[j]);
        j += 1;
    }

    for i in 0..merged.len() {
        list[start + i] = merged[i];
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_merge_with_sorted_lists() {
        let mut vec = vec![1, 3, 5, 2, 4, 6];
        let len = vec.len();
        merge_sort(&mut vec, 0, len);
        assert_eq!(vec, vec![1,2,3,4,5,6]);
    }

    #[test]
    fn test_merge_with_empty_lists() {
        let mut vec = vec![];
        let len = vec.len();
        merge_sort(&mut vec, 0, len);
        assert_eq!(vec, vec![]);
    }

    #[test]
    fn test_merge_with_one_element_lists() {
        let mut vec = vec![1, 0];
        let len = vec.len();
        merge_sort(&mut vec, 0, len);
        assert_eq!(vec, vec![0, 1]);
    }

    #[test]
    fn test_merge_with_same_elements() {
        let mut vec = vec![1, 1, 1, 1, 1, 1];
        let len = vec.len();
        merge_sort(&mut vec, 0, len);
        assert_eq!(vec, vec![1, 1, 1, 1, 1, 1]);
    }

    #[test]
    fn test_merge_with_negative_elements() {
        let mut vec = vec![-1, -3, -5, -2, -4, -6];
        let len = vec.len();
        merge_sort(&mut vec, 0, len);
        assert_eq!(vec, vec![-6, -5, -4, -3, -2, -1]);
    }

    #[test]
    fn test_merge_sort_with_partially_sorted_vec() {
        let mut vec = vec![5, 2, 9, 1, 7, 6, 8, 3, 4];
        let len = vec.len();
        merge_sort(&mut vec, 4, len);
        assert_eq!(vec, vec![5, 2, 9, 1, 3, 4, 6, 7, 8]);
    }

    #[test]
    fn test_merge_sort_with_duplicate_elements() {
        let mut vec = vec![5, 2, 9, 1, 7, 2, 8, 3, 4];
        let len = vec.len();
        merge_sort(&mut vec, 0, len);
        assert_eq!(vec, vec![1, 2, 2, 3, 4, 5, 7, 8, 9]);
    }

    #[test]
    fn test_merge_sort_with_negative_elements() {
        let mut vec = vec![-5, -2, -9, 1, -7, 6, -8, 3, 4];
        let len = vec.len();
        merge_sort(&mut vec, 0, len);
        assert_eq!(vec, vec![-9, -8, -7, -5, -2, 1, 3, 4, 6]);
    }

    #[test]
    fn test_merge_sort_with_random_elements() {
        let mut vec = vec![5, 4, 2, 1, 3, 6, 7, 8, 9];
        let len = vec.len();
        merge_sort(&mut vec, 0, len);
        assert_eq!(vec, vec![1, 2, 3, 4, 5, 6, 7, 8, 9]);
    }
}
