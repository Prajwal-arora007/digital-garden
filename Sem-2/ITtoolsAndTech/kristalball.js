var input = {
    id: "SE1",
    data: 10,
    left: {
      id: "SE2",
      data: 12,
      left: {
        id: "SE4",
        data: 4,
        right: {
          id: "SE8",
          data: 9,
          left: {
            id: "SE15",
            data: 20,
          },
        },
      },
      right: {
        id: "SE5",
        data: 17,
        left: {
          id: "SE9",
          data: 10,
          left: {
            id: "SE16",
            data: 8,
            right: {
              id: "SE17",
              data: 18,
            },
          },
        },
        right: {
          id: "SE10",
          data: 11,
        },
      },
    },
    right: {
      id: "SE3",
      data: 7,
      left: {
        id: "SE6",
        data: 6,
        left: {
          id: "SE11",
          data: 18,
        },
        right: {
          id: "SE12",
          data: 2,
        },
      },
      right: {
        id: "SE7",
        data: 3,
        left: {
          id: "SE13",
          data: 13,
        },
        right: {
          id: "SE14",
          data: 15,
        },
      },
    },
  };
  
  var lineWithHighestSales = function (data, bonus) {
    const findBestLine = (node) => {
      if (!node) return { line: [], totalSales: 0 };
  
      const leftResult = findBestLine(node.left);
      const rightResult = findBestLine(node.right);
  

      const bestSubPath =
        leftResult.totalSales > rightResult.totalSales
          ? leftResult
          : rightResult;
  
      return {
        line: [{ id: node.id, sales: node.data }].concat(bestSubPath.line),
        totalSales: node.data + bestSubPath.totalSales,
      };
    };
  
    const bestLineResult = findBestLine(data);
    const bestLine = bestLineResult.line;
    const totalSales = bestLineResult.totalSales;
  
    const budgetEfficiencyBonus = bonus * 0.25; 
    const salesEfficiencyBonus = bonus * 0.75; 
    const totalSubordinates = bestLine.length - 1; 
    return bestLine.map((employee, index) => {

      const subordinateShare =
        totalSubordinates > 0
          ? (index / totalSubordinates) * budgetEfficiencyBonus
          : 0;
  
      const salesShare = (employee.sales / totalSales) * salesEfficiencyBonus;
  

      return {
        id: employee.id,
        bonus: subordinateShare + salesShare,
      };
    });
  };
  
  var bonus = 3000000; 
  var line = lineWithHighestSales(input, bonus);
  
  console.log("Result :" + JSON.stringify(line));
  

  var expectedLine = [
    { id: "SE1", bonus: 550000 },
    { id: "SE2", bonus: 560000 },
    { id: "SE5", bonus: 660000 },
    { id: "SE9", bonus: 400000 },
    { id: "SE16", bonus: 290000 },
    { id: "SE17", bonus: 540000 },
  ];
  
  console.log("Expected Result :" + JSON.stringify(expectedLine));
  