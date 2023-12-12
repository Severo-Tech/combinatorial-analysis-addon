// eslint-disable-next-line import/extensions
// @ts-ignore
import combinationsAddon from '../../build/Release/combinations-addon.node';

export interface ICombinationsValue {
  id: string;
  value: number | string;
}

export class Combinations {
  public byValue<T extends ICombinationsValue>(list: T[], target: number): T[][] {
    const innerList = this.convertListToAddonAdapter(list);

    const combinations = combinationsAddon.combineByValue(innerList, target);

    return this.convertAddonResultToCombinationsList(list, combinations);
  }

  private convertListToAddonAdapter<T extends ICombinationsValue>(list: T[]): number[][] {
    return list.map((el: T, index: number): number[] => [index, +el.value]);
  }

  private convertAddonResultToCombinationsList<T extends ICombinationsValue>(originalList: T[], combinations: number[][][]): T[][] {
    return combinations.map(
      (el: number[][]): T[] => el.map((combination: number[]): T => ({
        ...originalList[combination[0]],
      })),
    );
  }
}

export const combinations = new Combinations();
