pub fn selection_sort(list: &mut Vec<i32>) {
    let len = list.len();
    let mut min_index;

    for i in 0..len {
        min_index = i;
        for j in i..len {
            if list[min_index] > list[j] {
                min_index = j;
            }
        }
        list.swap(min_index, i);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_empty_list() {
        let mut empty_list = Vec::new();
        selection_sort(&mut empty_list);
        assert_eq!(empty_list, Vec::new());
    }

    #[test]
    fn test_one_element_list() {
        let mut one_element_list = vec![1];
        selection_sort(&mut one_element_list);
        assert_eq!(one_element_list, vec![1]);
    }

    #[test]
    fn test_sorted_list() {
        let mut sorted_list = vec![1, 2, 3, 4, 5];
        selection_sort(&mut sorted_list);
        assert_eq!(sorted_list, vec![1, 2, 3, 4, 5]);
    }

    #[test]
    fn test_reverse_sorted_list() {
        let mut reverse_sorted_list = vec![5, 4, 3, 2, 1];
        selection_sort(&mut reverse_sorted_list);
        assert_eq!(reverse_sorted_list, vec![1, 2, 3, 4, 5]);
    }

    #[test]
    fn test_random_list() {
        let mut random_list = vec![3, 2, 4, 1, 5];
        selection_sort(&mut random_list);
        assert_eq!(random_list, vec![1, 2, 3, 4, 5]);
    }

    #[test]
    fn test_negative_list() {
        let mut random_list = vec![-3, -2, 0, -1, 5];
        selection_sort(&mut random_list);
        assert_eq!(random_list, vec![-3, -2, -1, 0, 5]);
    }

    #[test]
    fn test_duplicate_list() {
        let mut random_list = vec![-5, -3, -3, -3, 0, 0, -11, 10, 20, 5];
        selection_sort(&mut random_list);
        assert_eq!(random_list, vec![-11, -5, -3, -3, -3, 0, 0, 5, 10, 20]);
    }

}

