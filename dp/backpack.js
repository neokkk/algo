const w = [4, 3, 1, 5];
const v = [5, 4, 1, 7];

function solution(w, v, target) {
  const save = Array(w.length).fill(0).map(() => Array(target + 1).fill(0));

  for (let i = 0; i < w.length; i++) {
    for (let j = 1; j <= target; j++) {
      if (i === 0) {
        save[i][j] = v[i];
      } else {
        if (j < w[i]) {
          save[i][j] = save[i - 1][j];
        } else {
          // 자신을 포함하는 경우
          let includeValue = v[i] + save[i - 1][j - w[i]];

          // 포함하지 않는 경우
          let notIncludeValue = save[i - 1][j];

          save[i][j] = Math.max(includeValue, notIncludeValue);
        }
      }
    }
  }
  console.log(save);
}

solution(w, v, 7);


function knapsack() {
    const items = [null, { w: 4, v: 5 } , { w: 3, v: 4 }, { w: 1, v: 1 }, { w: 5, v: 7 }];
    let capacity = 7;
    let table = Array.from({length: items.length }, () => null);
  
    /*
  
  [ [ 0, 0, 0, 0, 0, 0, 0, 0 ],
    [ 0, 0, 0, 0, 0, 0, 0, 0 ],
    [ 0, 0, 0, 0, 0, 0, 0, 0 ],
    [ 0, 0, 0, 0, 0, 0, 0, 0 ],
    [ 0, 0, 0, 0, 0, 0, 0, 0 ] ]
  
    */
    for (let i  = 0; i < table.length; i++) {
      table[i] = [...new Array(capacity + 1).fill(0)];
    }
  
    console.log(table);
  
    for (let i = 1; i < items.length; i++) {
      for (let j = 1; j < capacity + 1; j++) { 
        let result = 0;
  
        if(j < items[i].w) {
          result = table[i - 1][j]
        }
        else {
          result = Math.max(items[i].v + table[i - 1][j - items[i].w], table[i - 1][j])
        }
  
        table[i][j] = result;
      }
    }
    
    console.dir(table);
  }
  
  knapsack()